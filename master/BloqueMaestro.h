//
// Created by FuryCoder on 1/9/2018.
//

#ifndef DCLI_BLOQUEMAESTRO_H
#define DCLI_BLOQUEMAESTRO_H

#include <stdio.h>
#include <string.h>
#include <list>
#include "DataFile.h"

class BloqueMaestro {
    public:
        BloqueMaestro();
        BloqueMaestro(int dbSize,int blockSize);


        void Write(DataFile*);
        void Load(DataFile*);
        void getBlockSize(DataFile*);
        virtual ~BloqueMaestro();

        //variables
        int blockSize;
        int blockNumber;
        int dbSize;
        int maxBlocks;
        int firstTableBlock =1;
        int lastTableBlock;
        int nextAvaBlock;
    protected:

    private:
        char *toChar();
        void charToBlock(char*data);
};


#endif //DCLI_BLOQUEMAESTRO_H
