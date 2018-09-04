//
// Created by FuryCoder on 1/9/2018.
//

#include "DataFile.h"

DataFile::DataFile(char *path){
    this->path = path;
//    this->dbSize=dbSize;
//    this->blockSize=blockSize;
}

void DataFile::Write(char *data, int pos, int longitud) {
    openFile();
    if(fseek(archivo,pos,SEEK_SET)==0){
        fwrite(data,sizeof(char),longitud,archivo);
    }
    closeFile();
}

char *DataFile::Read(int pos, int longitud) {
    openFile();
    char *buffer = new char[longitud];
    if(fseek(archivo,pos,SEEK_SET)==0){
        fread(buffer, sizeof(char),longitud,archivo);
    }
    closeFile();
    return buffer;
}

void DataFile::openFile() {
    archivo = fopen(path,"rb+");
}

void DataFile::closeFile() {
    fclose(archivo);
}

void DataFile::createFile() {
    archivo = fopen(path,"wb");
    closeFile();
}

int DataFile::deleteFile(char *path) {
    return remove(path);
}
