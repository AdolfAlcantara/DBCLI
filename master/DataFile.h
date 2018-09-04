//
// Created by FuryCoder on 1/9/2018.
//

#ifndef DCLI_DATAFILE_H
#define DCLI_DATAFILE_H


#include <fstream>
using namespace std;

class DataFile {

    //atributes
    public:
        char* path;
        FILE *archivo;

        DataFile(char *path);
        void createFile();
        int deleteFile(char *path);
        void openFile();
        void closeFile();
        void Write(char*data,int pos, int longitud);
        char * Read(int pos, int longitud);



};


#endif //DCLI_DATAFILE_H
