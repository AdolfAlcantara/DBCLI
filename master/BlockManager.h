//
// Created by FuryCoder on 2/9/2018.
//

#ifndef DCLI_BLOCKMANAGER_H
#define DCLI_BLOCKMANAGER_H


#include "DataFile.h"
#include "BloqueMaestro.h"
#include "../blocks/TableBlock.h"

class BlockManager {

public:
    BlockManager(DataFile*);
    int nextAvaBlock();
    TableBlock* asignBlockTable();
    TableBlock* LoadTableBlock(int bn);

    DataFile *archivo;
    BloqueMaestro *bm = new BloqueMaestro();
};


#endif //DCLI_BLOCKMANAGER_H
