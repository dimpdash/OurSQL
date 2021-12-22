#pragma once
#include "Field.h"
#include <fstream>
#include <vector>

class Row
{
public:
	Row(const Row&) = delete;
	Row(Row&&) = default;
	Row(vector<std::unique_ptr<Field>>&& fields);
	~Row() = default;
	vector<std::unique_ptr<Field>> fields;
	int totalSize;
	
	void parse(ifstream &rf);
	void write(ofstream& wf);
	int getTotalSize();
	unique_ptr<Row> copyRow();
	vector<std::unique_ptr<Field>> getNewFields() const;
};

