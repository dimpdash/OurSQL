#include "Table.h"
#include "Block.h"
#include "BlockManager.h"
#include "IndexManager.h"
#include "Row.h"
#include<iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int Table::readRows(vector<Row*> &rstu, int size) {
    auto& blocks = blockManager->getBlocks();
    blocks.begin();

    for (auto const& block : blocks) {
        block->readRows(rstu, headerRow);
    }
    return 1;
}

unique_ptr<ITable> Table::select(int key) {
    auto table = make_unique<MemoryTable>();

     IntField field(key);
     auto blockIds = this->indexManager->index(field);
     for (auto bid : blockIds) {
         auto block = blockManager->getBlock(bid);
         vector<Row*> rows;
         block->readRows(rows,headerRow);

         for (auto r : rows) {
             if (field  == *r->fields.at(0).get()) {
                 auto addRows = vector<unique_ptr<Row>>();
                 addRows.push_back(r->copyRow());
                 table->writeRows(addRows);
             }
         }
    }
    
    return std::move(table);
}

int Table::writeRows(vector<unique_ptr<Row>> &rows) {
    blockManager->writeBlocks(rows);
    return 1;
}

void Table::deleteRowByKey(Field& key) {
    auto blockId = indexManager->getBlock(key);
    /*auto& block = blockManager->getBlocks().at(blockId);*/
    //TODO
    //block->deleteRow(key);
}

int Table::readRows(vector<Row*>& rstu) {
    auto& blocks = blockManager->getBlocks();
    blocks.begin();

    for (auto const& block : blocks) {
        block->readRows(rstu, headerRow);
    }
    return 1;
}


Table::Table(string name, unique_ptr<Row> headerRow)
{
    this->dir = ".\\" + name;
    this->name = name;
    //TODO use meta data to determine if should delete
    fs::remove_all(dir);
    fs::create_directory(name);
    this->headerRow = std::move(headerRow);

    this->indexManager = std::make_shared<IndexManager>(dir);
    auto observers = vector<weak_ptr<IBlockUpdateObserver>>();
    observers.push_back((weak_ptr<IndexManager>)indexManager);

    this->blockManager = std::make_unique<BlockManager>(dir,observers);
}


Table::~Table()
{
}