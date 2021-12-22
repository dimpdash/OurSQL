#pragma once
#include <string>
#include <vector>;
#include "Block.h"
#include "Row.h"
#include "BlockManager.h"
#include "IndexManager.h"

using namespace std;

class ITable
{
public:
    virtual int readRows(vector<Row*>& rows, int size) = 0;
    virtual int readRows(vector<Row*>& rows)=0;
    virtual unique_ptr<ITable> select(int key)=0;
    virtual int writeRows(vector<unique_ptr<Row>> &rows)=0;
};

class Table : public ITable
{
public:
    Table(string name, unique_ptr<Row> headerRow);
    ~Table();

    int readRows(vector<Row*>& rows, int size) override;
    int readRows(vector<Row*> &rows) override;
    unique_ptr<ITable> select(int key) override;
    int writeRows(vector<unique_ptr<Row>> &rows) override;
    void deleteRowByKey(Field& field);

private:
    string name;
    string dir;
    std::unique_ptr<BlockManager> blockManager;
    std::shared_ptr<IndexManager> indexManager;
    std::unique_ptr<Row> headerRow;
};

class MemoryTable : public ITable {
public:
    MemoryTable(vector<unique_ptr<Row>> _rows);
    MemoryTable();
    ~MemoryTable();

    int readRows(vector<Row*>& rows, int size) override;
    int readRows(vector<Row*>& rows) override;
    unique_ptr<ITable> select(int key) override;
    int writeRows(vector<unique_ptr<Row>> &rows) override;

private:
    vector<unique_ptr<Row>> rows;
    unique_ptr<Row> header_row;
};

