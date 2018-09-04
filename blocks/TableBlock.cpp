//
// Created by FuryCoder on 2/9/2018.
//

#include <iostream>
#include "TableBlock.h"

TableBlock::TableBlock(int blockSize, int bn) {
    this->blockSize=blockSize;
    this->blockNumber = bn;
}

Table* TableBlock::getTable(string name) {
    for(auto it = tables->begin();it!=tables->end();it++){
        Table *tb = *it;
        string str(tb->tableName);
        if(str.compare(name)==0){
            return tb;
        }
    }
    return nullptr;
}

bool TableBlock::deleteTable(string name)
{
    Table *tb = getTable(name);
    if(tb != nullptr){
        tables->remove(tb);
        this->tablesCount--;
        return true;
    }
    return false;

}

void TableBlock::listTables() {
    if(tables->empty()){
        return;
    }
    for(auto it = tables->begin();it!=tables->end();it++){
        Table *tb = *it;
        std::cout<<tb->tableName<<endl;
    }
}


bool TableBlock::fitsTable(Table *tb){
    int actualTable = calculateTableSize(tb);

    int totalBlockSpace=12;
    if(tablesCount>0){
        for(auto it = tables->begin();it!=tables->end();it++){
            totalBlockSpace+=calculateTableSize(*it);
        }
    }
    return (totalBlockSpace+actualTable<blockSize);


}

int TableBlock::calculateTableSize(Table *tb) {
    int tableSize=26;
    string str(tb->tableName);
    tableSize+=str.size()+1;
    tableSize+=tb->fieldCount*8;
    if(tb->fieldCount>0) {
        for (auto it = tb->Fields->begin(); it != tb->Fields->end(); it++) {
            Field *fl = *it;
            tableSize += fl->size;
        }
    }
    return tableSize;
}

void TableBlock::write(DataFile *df) {
    char *data = toChar();
    int pos = blockNumber * blockSize;
    df->Write(data,pos,blockSize);
}

void TableBlock::load(DataFile *df) {
    int pos = blockNumber * blockSize;
    char *data = df->Read(pos,blockSize);
    charToBlock(data);
}

char * TableBlock:: toChar() {
    char *data  = new char [blockSize];
    int pos =0;
    memcpy(&data[pos],&blockNumber,4);
    pos+=4;
    memcpy(&data[pos],&nextBlock,4);
    pos+=4;
    memcpy(&data[pos],&tablesCount,4);
    pos+=4;
    if(tablesCount!=0){
        for(auto it=tables->begin(); it != tables->end(); it++){
            Table *x = *it;
            int tbns = x->tabNameSize;
            memcpy(&data[pos],&x->tabNameSize,4);
            pos+=4;
            memcpy(&data[pos],&x->tableName[0],tbns);
            pos+=tbns;
            memcpy(&data[pos],&x->iFieldBlock,4);
            pos+=4;
            memcpy(&data[pos],&x->fFieldBlock,4);
            pos+=4;
            memcpy(&data[pos],&x->fieldCount,4);
            pos+=4;
            for(auto itc=x->Fields->begin(); itc != x->Fields->end(); itc++){
                Field* fl = *itc;
                memcpy(&data[pos],&fl->dataType,4);
                pos+=4;
                memcpy(&data[pos],&fl->size,4);
                pos+=4;
                memcpy(&data[pos],&fl->fieldName[0],fl->size);
                pos+=fl->size;
            }
        }
    }
    return data;
}

void TableBlock::charToBlock(char *data) {
    int pos=0;
    memcpy(&blockNumber,&data[pos],4);
    pos+=4;
    memcpy(&nextBlock,&data[pos],4);
    pos+=4;
    memcpy(&tablesCount,&data[pos],4);
    pos+=4;
    for(int i=0; i<tablesCount;i++){
        int tbns;
        memcpy(&tbns,&data[pos],4);
        pos+=4;
        char *name = new char[tbns];
        memcpy(&name[0],&data[pos],tbns);
        pos+=tbns;
        string str(name);
        Table* nt = new Table(str);
        memcpy(&nt->iFieldBlock,&data[pos],4);
        pos+=4;
        memcpy(&nt->fFieldBlock,&data[pos],4);
        pos+=4;
        memcpy(&nt->fieldCount,&data[pos],4);
        pos+=4;
        for(int x=0;x<nt->fieldCount;x++){
            int dataType,size;
            memcpy(&dataType,&data[pos],4);
            pos+=4;
            memcpy(&size,&data[pos],4);
            pos+=4;
            char* temp = new char[size];
            memcpy(&temp[0],&data[pos],size);
            pos+=size;
            string str(temp);
            Field *fl = new Field(str,dataType);
            nt->Fields->push_back(fl);
        }
        tables->push_back(nt);
    }
}