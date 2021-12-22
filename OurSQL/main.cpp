#include "Table.h"
#include "Row.h"
#include "Field.h"
#include "Block.h"
#include <string>
#include <vector>

#include<iostream>

using namespace std;

#define NUM_OF_STUDENTS 6

static vector<weak_ptr<IBlockUpdateObserver>> defaultObservers;

void write_test_blocks() {
    Block block(1, ".\\test\\block", defaultObservers);
    vector<unique_ptr<Row>> rows;
    vector<unique_ptr<Field>> fields;
    fields.push_back(make_unique<IntField>(6));
    fields.push_back(make_unique<IntField>(8));
    rows.push_back(make_unique<Row>(std::move(fields)));

    block.writeRows(rows, 0);

}

void write_test_heap_index() {
    vector<unique_ptr<Field>> fields;
    fields.push_back(make_unique<IntField>(6));
    fields.push_back(make_unique<IntField>(8));

    HeapIndex index("test heapindex", ".\\");
    index.addRows(fields, 0);

}

void write_test_index_manager() {
    IndexManager indexManager(".\\test");
    vector<shared_ptr<Row>> rows;
    vector<unique_ptr<Field>> fields;
    fields.push_back(make_unique<IntField>(6));
    fields.push_back(make_unique<IntField>(8));
    rows.push_back(make_shared<Row>(std::move(fields)));

    indexManager.rowsWrittenToBlock(rows, 5);
}
//
//void write_test_block_update_observer() {
//
//    vector<weak_ptr<IBlockUpdateObserver>> observers;
//    observers.push_back(weak_ptr<>)
//
//    Block block(1, ".\\test\\block_update_observer", observers);
//    vector<unique_ptr<Row>> rows;
//    vector<unique_ptr<Field>> fields;
//    fields.push_back(make_unique<IntField>(6));
//    fields.push_back(make_unique<IntField>(8));
//    rows.push_back(make_unique<Row>(std::move(fields)));
//
//}

int main() {

    //write_test_blocks();
    //write_test_heap_index();
    //write_test_index_manager();
    vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::make_unique<IntField>());
    fields.push_back(std::make_unique<IntField>());
    fields.push_back(std::make_unique<IntField>());
    auto headerRow = make_unique<Row>(std::move(fields));
    Table table("student", std::move(headerRow));

    vector<unique_ptr<Row>> rows;
    for (int i = 0; i < NUM_OF_STUDENTS; i++) {
        auto f1 = std::make_unique<IntField>(i);
        auto f2 = std::make_unique<IntField>(8);
        auto f3 = std::make_unique<IntField>(10);
        vector<std::unique_ptr<Field>> fields;
        fields.push_back(std::move(f1));
        fields.push_back(std::move(f2));
        fields.push_back(std::move(f3));
        rows.push_back(make_unique<Row>(std::move(fields)));
    }

    cout << "Writing rows" << endl;
    table.writeRows(rows);

    cout << "Get rows" << endl;
    vector<Row*> rstu;
    table.readRows(rstu, NUM_OF_STUDENTS);

    cout << "Student's Details:" << endl;
    for (Row* row : rstu) {
        for (auto& f : row->fields) {
           cout << f->getString();
           cout << " | ";
        }
        cout << endl;
    }

    auto tSelect = table.select(2);

    vector<Row*> selectRows;
    tSelect->readRows(selectRows);

    cout << "Selected Rows" << endl;
    for (Row* row : selectRows) {
        for (auto& f : row->fields) {
            cout << f->getString();
            cout << " | ";
        }
        cout << endl;
    }

    return 0;
}
