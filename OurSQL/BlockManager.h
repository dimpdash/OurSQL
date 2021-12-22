#pragma once
#include "Block.h"
#include <vector>
#include <string>
#include <map>
#include "IBlockUpdateObserver.h"
using namespace std;

class BlockManager
{
public:
	BlockManager(const BlockManager&) = delete;
	BlockManager(BlockManager&&) = default;
	BlockManager(string path, vector<weak_ptr<IBlockUpdateObserver>>& observers);
	void saveBlocks(vector<Block> blocks);
	void writeBlocks(const vector<unique_ptr<Row>>& rows);
	Block* getBlock(int id);

	vector<unique_ptr<Block>>& getBlocks();
	string dir;
	string filename;
private:
	
	vector<weak_ptr<IBlockUpdateObserver>> observers;
	vector<unique_ptr<Block>> blocks;

};

class OpenAddressingBlockManager
{
public:
	OpenAddressingBlockManager(const OpenAddressingBlockManager&) = delete;
	OpenAddressingBlockManager(OpenAddressingBlockManager&&) = default;
	OpenAddressingBlockManager(string path, vector<weak_ptr<IBlockUpdateObserver>>& observers);
	void writeRow(unique_ptr<Row>& row, int index);
	Block* getBlock(int id);
	map<int, unique_ptr<Block>>& getBlocks();
	string dir;
	string filename;

private:
	vector<weak_ptr<IBlockUpdateObserver>> observers;
	map<int, unique_ptr<Block>> blocks;
};
