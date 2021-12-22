#pragma once

#include "Index.h"

HashIndex::HashIndex(string id, string dir) {
	auto observers = vector<weak_ptr<IBlockUpdateObserver>>();
	blockManager = std::make_unique<OpenAddressingBlockManager>(dir, observers);
	auto fields = vector<unique_ptr<Field>>();
	fields.push_back(make_unique<IntField>());
	fields.push_back(make_unique<IntField>());
	headerRow = make_unique<Row>(std::move(fields));
}

int HashIndex::hash(int key) {
	return key % 11; //choose prime for better uniform distribution
}

vector<int>  HashIndex::index(Field& key) {
	auto currBlockId = hash(dynamic_cast<IntField&>(key).val);

	//TODO probe through
	return std::vector<int>(currBlockId);
}

int HashIndex::getBlock(Field& key) {
	for (auto& block : blockManager->getBlocks()) {
		auto rows = vector<Row*>();
		block.second->readRows(rows, headerRow);
		for (auto row : rows) {
			if (*(row->fields.at(0).get()) == key) {
				auto& blockField = row->fields.at(1);
				return dynamic_cast<unique_ptr<IntField>&>(*blockField)->val;
			}
		}
	}
	return -1;
}


void HashIndex::addRows(vector<unique_ptr<Field>>& keys, int blockid) {
	for (auto& key : keys) {
		auto fields = vector<unique_ptr<Field>>();
		fields.push_back(std::move(key->copyField()));
		fields.push_back(make_unique<IntField>(blockid));
		auto row = make_unique<Row>(std::move(fields));
		blockManager->writeRow(row, blockid);
	}
}

