#include "Row.h"
#include "Field.h"
#include <vector>
#include <fstream>
using namespace std;

Row::Row(vector<std::unique_ptr<Field>>&& fields) {
	this->fields = std::move(fields);
}

void Row::parse(ifstream &rf) {
	for (auto& f : fields) {
		f->read(rf);
	}
}

void Row::write(ofstream &wf) {
	for (auto& f : fields) {
		f->write(wf);
	}
}

int Row::getTotalSize() {
	int size = 0;
	for (auto& f : fields) {
		size += f->getSize();
	}
	return size;
}

vector<unique_ptr<Field>> Row::getNewFields() const {
	vector<unique_ptr<Field>> v;

	for (auto& f : fields) {
		v.push_back(f.get()->newField());
	}
	return v;
}

unique_ptr<Row> Row::copyRow() {
	auto new_fields = vector<unique_ptr<Field>>();
	for (auto& f : this->fields) {
		new_fields.push_back(f->copyField());
	}

	return make_unique<Row>(std::move(new_fields));
}
