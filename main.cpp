#include "database.h"
#include <iostream>

int main()
{
    Database db;

    db.createTables();
    db.addText("1", "2", "3", 4, "5");
    for (Text t: db.getAllTexts())
    {
        std::cout << t.id << '\t' << t.title << '\n';
    }

    // int a = 5;
    // void* b = &a;

    // int* c = static_cast<int*>(b); // C++
    // int* d = (int*)b; // C
}
