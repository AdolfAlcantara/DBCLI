//
// Created by FuryCoder on 2/9/2018.
//

#include "Table.h"

Table::Table(string tableName)
{
    this->tabNameSize = tableName.size()+1;
    this->tableName = new char[this->tabNameSize];
    copy(tableName.begin(),tableName.end(),this->tableName);
    this->tableName[tableName.size()] = '\0';
    Fields = new std::list<Field*>;
}
