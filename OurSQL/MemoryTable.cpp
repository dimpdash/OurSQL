#include "Table.h"

MemoryTable::MemoryTable(vector<unique_ptr<Row>> _rows)
{
	this->rows = std::move(_rows);
}
int MemoryTable::readRows(vector<Row*>& rows) {
	for (auto& row : this->rows) {
		rows.push_back(row.get());
	}
	return 0;
}

int MemoryTable::readRows(vector<Row*>& rows, int size) {
	//for (auto& row : this->rows) {
	//	rows.push_back(row.get());
	//}

	return 0;
}

unique_ptr<ITable> MemoryTable::select(int key) {
	auto f = IntField(key);

	auto rowSelected = vector<unique_ptr<Row>>();
	for (auto& row : this->rows) {
		if (*row->fields.at(0).get() == f) {
			rowSelected.push_back(row->copyRow());
		}
	}

	 return make_unique<MemoryTable>(std::move(rowSelected));
	return make_unique<MemoryTable>();

}

int MemoryTable::writeRows(vector<unique_ptr<Row>> &rows) {
	this->rows = std::move(rows);
	return 0;
}

MemoryTable::~MemoryTable() {

}

MemoryTable::MemoryTable() {

}