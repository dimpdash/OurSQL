#pragma once

#include "Index.h"


int HeapIndex::getBlock(Field& key) {
	for (auto& block : blockManager->getBlocks()) {
		auto rows = vector<Row *>();

		block->readRows(rows, headerRow);
		for (auto row : rows) {
			if (*(row->fields.at(0).get()) == key) {
				auto& blockField = row->fields.at(1);
				return dynamic_cast<unique_ptr<IntField>&>(*blockField)->val;
			}
		}
	}
	return -1;
}

void HeapIndex::addRows(vector<unique_ptr<Field>>& keys, int blockid) {
	auto rows = vector<unique_ptr<Row>>();
	for (auto& key : keys) {
		auto fields = vector<unique_ptr<Field>>();
		fields.push_back(std::move(key->copyField()));
		fields.push_back(make_unique<IntField>(blockid));
		rows.push_back(make_unique<Row>(std::move(fields)));
	}
	blockManager->writeBlocks(rows);
}

vector<int> HeapIndex::index(Field& f) {
	auto result = vector<int>();

	for (auto& b : blockManager->getBlocks()) {
		auto rows = vector<Row*>();
		b->readRows(rows, headerRow);
		for (auto& r : rows) {
			if (f == *r->fields.at(0).get()) {
				auto bRow =r->fields.at(1).get();
				result.push_back(dynamic_cast<IntField*>(bRow)->val);
			}
		}
	}

	return result;
}

HeapIndex::HeapIndex(string id, string dir) {
	auto observers = vector<weak_ptr<IBlockUpdateObserver>>();
	blockManager = std::make_unique<BlockManager>(dir, observers);
	auto fields = vector<unique_ptr<Field>>();
	fields.push_back(make_unique<IntField>());
	fields.push_back(make_unique<IntField>());
	headerRow = make_unique<Row>(std::move(fields));
}
