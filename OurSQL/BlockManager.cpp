#include "BlockManager.h"
#include "Row.h"
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

void BlockManager::saveBlocks(vector<Block> blocks) {
    // Write out a list to a disk file
    {
        ofstream os(this->dir + "\\" + this->filename + ".dat", ios::binary);
    }
}

void BlockManager::writeBlocks(const vector<unique_ptr<Row>>& rows) {
    //TODO check if preexisting blocks
    auto len = rows.size();
    int start;
    if (blocks.size() == 0) {
        auto block = make_unique<Block>(blocks.size(), dir, observers);
        start = block->writeRows(rows, 0);
        blocks.push_back(std::move(block));
    }
    else {
        auto& lastBlock = blocks.at(blocks.size() - 1);
        if (!lastBlock->isFull()) {
            start = lastBlock->writeRows(rows, lastBlock->getNumEntries());
        }
        else {
            auto block = make_unique<Block>(blocks.size(), dir, observers);
            start = block->writeRows(rows, 0);
            blocks.push_back(std::move(block));
        }
    }


    bool notFull = start < len - 1;
    while (notFull) {
        auto block = make_unique<Block>(blocks.size(), dir, observers);
        start += block->writeRows(rows, 0);
        blocks.push_back(std::move(block));

        notFull = start < len - 1;
    }
}

Block* BlockManager::getBlock(int id) {
    return blocks.at(id).get();
}

vector<unique_ptr<Block>>& BlockManager::getBlocks() {
    return blocks;
}

BlockManager::BlockManager(string path, vector<weak_ptr<IBlockUpdateObserver>>& observers) {
	this->filename = "blocks";
    this->dir = path;
    this->blocks = vector<unique_ptr<Block>>();
    this->observers = std::move(observers);
}