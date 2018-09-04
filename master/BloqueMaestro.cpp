//
// Created by FuryCoder on 1/9/2018.
//

#include <iostream>
#include "BloqueMaestro.h"

BloqueMaestro::BloqueMaestro()
{
    nextAvaBlock=2;
    lastTableBlock=1;
    blockSize=0;
    dbSize=0;
    maxBlocks=0;
    blockNumber=0;
}

BloqueMaestro::BloqueMaestro(int dbSize, int blockSize) {
    nextAvaBlock=2;
    lastTableBlock=1;
    this->dbSize = dbSize;
    this->blockSize = blockSize;
    maxBlocks  = dbSize/blockSize;
    blockNumber=0;
}

void BloqueMaestro::Write(DataFile *df) {
    int pos = blockNumber*blockSize;
    char *data = this->toChar();
    df->Write(data,pos,blockSize);
}

void BloqueMaestro::Load(DataFile *df) {
    getBlockSize(df);
    int pos = blockNumber*blockSize;
    char * data = df->Read(pos,blockSize);
    charToBlock(data);
}

//obtiene el tam;o del bloque que es el primer dato para poder
//leer el bloque completo
void BloqueMaestro::getBlockSize(DataFile *df)
{
    char * data = df->Read(0,4);
    memcpy(&blockSize,&data[0],4);
}

char * BloqueMaestro::toChar() {
    char *data  = new char [blockSize];
    int pos =0;
    memcpy(&data[pos],&blockSize,4);
    pos+=4;
    memcpy(&data[pos],&dbSize,4);
    pos+=4;
    memcpy(&data[pos],&maxBlocks,4);
    pos+=4;
    memcpy(&data[pos],&firstTableBlock,4);
    pos+=4;
    memcpy(&data[pos],&lastTableBlock,4);
    pos+=4;
    memcpy(&data[pos],&nextAvaBlock,4);
    return data;
}

void BloqueMaestro::charToBlock(char *data) {
    int pos =0;
    memcpy(&blockSize,&data[pos],4);
    pos+=4;
    memcpy(&dbSize,&data[pos],4);
    pos+=4;
    memcpy(&maxBlocks,&data[pos],4);
    pos+=4;
    memcpy(&firstTableBlock,&data[pos],4);
    pos+=4;
    memcpy(&lastTableBlock,&data[pos],4);
    pos+=4;
    memcpy(&nextAvaBlock,&data[pos],4);
}

BloqueMaestro::~BloqueMaestro() {

}
