#pragma once
#include <string>
#include <vector>;
#include "Row.h"
#include "IBlockUpdateObserver.h"

using namespace std;

class Block
{
public:
    Block(const Block&) = delete;
    Block(Block&&) = default;
    Block(int id, string path, vector<weak_ptr<IBlockUpdateObserver>> observers);
    ~Block();

    int readRows(vector<Row*> &rstu, const unique_ptr<Row>& headerrow) const;


    int writeRows(const vector<unique_ptr<Row>> &rows, int start);
    int writeRow(const unique_ptr<Row>& row);

    int getNumEntries();
    int getMaxSize();
    bool isFull();
    int getId();


private:
    int id;
    string path;
    int size;
    int maxSize;
    int entries;
    vector<weak_ptr<IBlockUpdateObserver>> observers;

    void notifyRowsWrittenToBlock(vector<shared_ptr<Row>>& rowsAdded);

};