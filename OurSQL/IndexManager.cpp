#include "IndexManager.h"
#include<iostream>
#include <filesystem>




IndexManager::IndexManager(string dir) {
	this->dir = dir;
	dir.append("\\indexes");
	fs::create_directory(dir);

	auto heapdir = dir + "\\heap";
	auto heapIndex = make_unique<HeapIndex>("heap", heapdir);
	fs::create_directory(heapdir);

	auto hashdir = dir + "\\hash";
	auto hashIndex = make_unique<HashIndex>("hash", hashdir);
	fs::create_directory(hashdir);

	addToIndexes(std::move(heapIndex));
	addToIndexes(std::move(hashIndex));
}

void IndexManager::addToIndexes(unique_ptr<Index> index) {
	this->indexes.push_back(std::move(index));
}

vector<int> IndexManager::index(Field& f) {
	auto& index = indexes.at(0);
	return index->index(f);
}

int IndexManager::getBlock(Field& key) {
	//TODO create optimiser
	//currently just get first index
	auto& index = indexes.at(0);
	return index->getBlock(key);
}

void IndexManager::addToIndexes(vector<shared_ptr<Row>>& rows, int blockid) {
	auto fields = vector<unique_ptr<Field>>();
	for (auto& r : rows) {
		//TODO currently assuming pk is always at index 0 and only indexing over pk
		fields.push_back(r->fields.at(0)->copyField());
	}
	for (auto& index : indexes) {
		index->addRows(fields, blockid);
	}
}

void IndexManager::rowsWrittenToBlock(vector<shared_ptr<Row>>& rows, int blockid) {
	addToIndexes(rows, blockid);
}
