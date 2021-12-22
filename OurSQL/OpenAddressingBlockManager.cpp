#pragma once
#include "BlockManager.h"
#include <map>
#include <memory>
#include <iostream>
#include <iomanip>
#include <memory>

void OpenAddressingBlockManager::writeRow(unique_ptr<Row>& row, int index) {
	bool init = true;



	if (blocks.count(index) != 0) {
		auto& currBlock = blocks.at(index);
		int i = 1;
		auto nextIndex = (index + i) % 11;
		while (!currBlock->isFull() && (index != currBlock->getId() || init)) {
			//TODO use external hash function
			if (blocks.count(nextIndex) != 0) {
				auto& currBlock = blocks.at(nextIndex);
			}
			else {
				blocks[nextIndex] = std::make_unique<Block>(nextIndex, dir, observers);
				auto& currBlock = blocks.at(nextIndex);
			}


			init = false;
			i++;
		}

		if (init == true || index != nextIndex) {
			currBlock->writeRow(row);
		}
		else {
			throw std::range_error("All Indexes are full");
		}

	}
	else {
		blocks[index] = std::make_unique<Block>(index, dir, observers);
		auto& currBlock = blocks.at(index);
		currBlock->writeRow(row);
	}
}


map<int, unique_ptr<Block>>& OpenAddressingBlockManager::getBlocks() {
	return blocks;
}

Block* OpenAddressingBlockManager::getBlock(int id) {
	return blocks.at(id).get();
}

OpenAddressingBlockManager::OpenAddressingBlockManager(string path, vector<weak_ptr<IBlockUpdateObserver>>& observers) {
	this->filename = "open addressing block manager";
	this->dir = path;
	this->blocks = map<int, unique_ptr<Block>>();
	this->observers = std::move(observers);

}