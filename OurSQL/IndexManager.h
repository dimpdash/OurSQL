#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Index.h"
#include "IBlockUpdateObserver.h"
#include "Field.h"

using namespace std;
namespace fs = std::filesystem;


class IndexManager : public IBlockUpdateObserver
{
public:
	IndexManager(const IndexManager&) = default;
	IndexManager(IndexManager&&) = default;
	IndexManager(string dir);
	void addToIndexes(unique_ptr<Index> index);
	vector<int> index(Field& f);
	int getBlock(Field& key);
	void addToIndexes(vector<shared_ptr<Row>>& rows, int blockid);
	void rowsWrittenToBlock(std::vector<shared_ptr<Row>>& rows, int blockid) override;


private:
	string dir;
	std::vector<std::unique_ptr<Index>> indexes;
};

