#pragma once
#include "Field.h"
#include "Block.h"
#include "BlockManager.h"

class Index
{
public:
	virtual int getBlock(Field& key) = 0;
	virtual void addRows(vector<unique_ptr<Field>>& keys, int blockid) = 0 ;
	virtual vector<int> index(Field& f) = 0;

private:
	string id;
	string dir;
};

class HeapIndex : public Index
{
public:
	HeapIndex(string id, string dir);
	int getBlock(Field& key) override;
	void addRows(vector<unique_ptr<Field>>& rows, int blockid) override;
	vector<int> index(Field& f) override;

private:
	vector<unique_ptr<Block>>* blocks;
	std::unique_ptr<BlockManager> blockManager;
	unique_ptr<Row> headerRow;
};

class HashIndex : public Index
{
public:
	HashIndex(string id, string dir);
	vector<int> index(Field& f) override;
	int getBlock(Field& key);
	void addRows(vector<unique_ptr<Field>>& keys, int blockid) override;
private:
	vector<unique_ptr<Block>>* blocks;
	std::unique_ptr<OpenAddressingBlockManager> blockManager;
	unique_ptr<Row> headerRow;
	int hash(int key);
};

