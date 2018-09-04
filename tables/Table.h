//
// Created by FuryCoder on 2/9/2018.
//

#ifndef DCLI_TABLE_H
#define DCLI_TABLE_H

#include <list>
#include <string>
#include "../fields/Field.h"

class Table {
public:
    Table(string tableName);

    char *tableName;
    int tabNameSize;
    int iFieldBlock=-1;
    int fFieldBlock=-1;
    int fieldCount=0;
    std::list<Field*>*Fields;


};


#endif //DCLI_TABLE_H
