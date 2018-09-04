//
// Created by FuryCoder on 2/9/2018.
//

#include "BlockManager.h"

BlockManager::BlockManager(DataFile *df) {
    archivo=df;
    archivo->openFile();
    bm->Load(archivo);
    archivo->closeFile();
}

int BlockManager::nextAvaBlock() {
    int next = bm->nextAvaBlock;
    bm->nextAvaBlock++;
    bm->Write(archivo);
    return next;
}

TableBlock * BlockManager::asignBlockTable()
{
    TableBlock*tb;
    int x = nextAvaBlock();
    if(x==1){
        tb = new TableBlock(bm->blockSize,x);
        bm->lastTableBlock = x;
        bm->Write(archivo);
//        ActualizarBloqueMaestro();
        tb->write(archivo);
        return tb;
    }
    tb = LoadTableBlock(bm->lastTableBlock);
    TableBlock* tb2 = new TableBlock(bm->blockSize,nextAvaBlock());
    tb ->nextBlock = tb2->blockNumber;
    bm->lastTableBlock = tb2->blockNumber;
    bm->Write(archivo);
//    ActualizarBloqueMaestro();
    tb->write(archivo);
    tb2->write(archivo);
    return tb2;
}

TableBlock * BlockManager::LoadTableBlock(int bn)
{
    TableBlock *tb = new TableBlock(bm->blockSize,bn);
    tb->load(archivo);
    return tb;
}

