#pragma once
#include "Block.h"
#include "Row.h"
#include "filesystem"
#include "iostream"


namespace fs = std::filesystem;

int Block::getNumEntries() {
    return this->entries;
}

int Block::getMaxSize() {
    return this->maxSize;
}

bool Block::isFull() {
    return this->entries >= maxSize;
}

int Block::writeRows(const vector<unique_ptr<Row>> &rows, int start) {
    auto len = rows.size();
    auto savePath = fs::path();
    savePath.append(path);
    savePath.append(std::to_string(id) + ".dat");


    ofstream wf(savePath, ios::out | ios::binary | ios::app);
    if (!wf) {
        cout << "Cannot open file!" << endl;
        return -2;
    }

    int i = start;

    auto rowsAdded = vector<shared_ptr<Row>>();
    for (; i < len && size < maxSize; i++) {
        auto& row = rows.at(i);
        row->write(wf);
        entries++;
        size += rows.at(i)->getTotalSize();
        rowsAdded.push_back(row->copyRow());

    }
    wf.close();
    if (!wf.good()) {
        cout << "Error occurred at writing time!" << endl;
        return -2;
    }

    notifyRowsWrittenToBlock(rowsAdded);



    return start + i;
}

int Block::writeRow(const unique_ptr<Row>& row) {
    auto savePath = fs::path();
    savePath.append(path);
    savePath.append(std::to_string(id) + ".dat");


    ofstream wf(savePath, ios::out | ios::binary | ios::app);
    if (!wf) {
        cout << "Cannot open file!" << endl;
        return -2;
    }

    row->write(wf);
    entries++;
    size += row->getTotalSize();

    wf.close();
    if (!wf.good()) {
        cout << "Error occurred at writing time!" << endl;
        return -2;
    }

    vector<shared_ptr<Row>> rowAdded;
    rowAdded.push_back(row->copyRow());

    notifyRowsWrittenToBlock(rowAdded);

    return 1;
}

void Block::notifyRowsWrittenToBlock(vector<shared_ptr<Row>>& rowsAdded) {
    for (auto o : observers) {
        if(auto obs =o.lock()) obs->rowsWrittenToBlock(rowsAdded, id);
    }
}

int Block::readRows(vector<Row*> &rstu, const unique_ptr<Row>& headerRow) const {
    ifstream rf(path + "\\" + std::to_string(id) + ".dat", ios::out | ios::binary);
    if (!rf) {
        throw std::invalid_argument("Cannot open file");
    }
    
    Row* row;
    for (int i = 0; i < entries; i++) {
        row = new Row(std::move(headerRow->getNewFields()));
        row->parse(rf);
        rstu.push_back(row);
    }

    rf.close();

    
    if (!rf.good()) {
        cout << rf.eof() << rf.fail() << rf.bad() << rf.rdstate() << endl;
        throw std::invalid_argument("Error Occured at reading time");
    }
}

int Block::getId() {
    return id;
}

Block::Block(int id, string path, vector<weak_ptr<IBlockUpdateObserver>> observers)
{
    this->path = path;
    this->id = id;
    this->size = 0;
    this->maxSize = 32+0*4*1024*8; //TODO revert to reasoable value
    this->entries = 0;
    this->observers = observers;
}

Block::~Block()
{
}