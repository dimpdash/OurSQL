#pragma once
#include<fstream>
#include<string>
using namespace std;

class Field
{
public:
	Field(const Field&) = default;
	Field& operator=(const Field&) = default;
	Field() = default;

	virtual void read(ifstream &rf)=0;
	virtual void write(ofstream &wf)=0;
	virtual string getString()=0;
	virtual int getSize()=0;
	virtual unique_ptr<Field> newField()=0;
	virtual unique_ptr<Field> copyField() = 0;

	friend bool operator==(Field const& lhs, Field const& rhs);
protected:
	virtual bool equals(Field const& field) const;

};

class IntField : public Field
{
public:
	IntField(int val);
	IntField();

	int val;
	string getString();
	void write(ofstream &wf);
	void read(ifstream &rf);
	int getSize();
	unique_ptr<Field> newField();
	unique_ptr<Field> copyField();

protected:
	virtual bool equals(const Field& field) const override;
};

