#include "Field.h"
#include <fstream>
#include <string>
using namespace std;

void IntField::write(ofstream &wf) {
	wf.write((char*)&this->val, sizeof(int));
}

void IntField::read(ifstream &rf) {
	rf.read((char*)&val, sizeof(int));
}

string IntField::getString() {
	return std::to_string(val);
}

int IntField::getSize() {
	return sizeof(int);
}

bool IntField::equals(Field const& other) const {
	if (IntField const* p = dynamic_cast<IntField const*>(&other)) {
		return val == p->val;
	}
	else {
		return false;
	}
}

unique_ptr<Field> IntField::newField() {
	return std::make_unique<IntField>();
}

unique_ptr<Field> IntField::copyField() {
	return std::make_unique<IntField>(val);
}

IntField::IntField(int x) {
	this->val = x;
}

IntField::IntField() {
	this->val = 0;
}

