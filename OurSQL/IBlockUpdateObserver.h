#pragma once
#include "Row.h"

class IBlockUpdateObserver {
public:
	virtual void rowsWrittenToBlock(std::vector<shared_ptr<Row>>& rows, int blockid) = 0;
};