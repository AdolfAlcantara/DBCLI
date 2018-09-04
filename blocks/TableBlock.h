//
// Created by FuryCoder on 2/9/2018.
//

#ifndef DCLI_TABLEBLOCK_H
#define DCLI_TABLEBLOCK_H

#include "../tables/Table.h"
#include "../master/DataFile.h"
#include "../master/BloqueMaestro.h"

class TableBlock {

    public:
        TableBlock(int blockSize, int bn);
        int blockNumber;
        int nextBlock=-1;
        int tablesCount=0;
        int blockSize;
        std::list<Table*>*tables = new std::list<Table*>;


        Table *getTable(string name);
        void listTables();
        bool deleteTable(string name);
        int calculateTableSize(Table*tb);
        bool fitsTable(Table *tb);
        void write(DataFile*);
        void load(DataFile*);

private:
    char *toChar();
    void charToBlock(char*data);
};


/*
 El tamano del header del bloque 12
 El tamano del header de la tabla es de 26
 Los campos de la tabla se sacan multiplicando la cantidad
 de campos por 8 (int del tamano e int del tipo de dato)
 Ademas sumar el valor del nombre del campo
 * */


#endif //DCLI_TABLEBLOCK_H
