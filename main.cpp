#include <iostream>
#include <string>
#include <sstream>
#include "./master/DataFile.h"
#include "master/BloqueMaestro.h"
#include "master/BlockManager.h"

using namespace std;

int main(){
    bool exit=false;
    string path = "C:\\Users\\FuryCoder\\Documents\\TBD2\\Proyecto2\\DCLI\\databases\\";
    DataFile *archivo;
    string dbName;
    do{
        int value = -1;
        std::cout<<"Que desea hacer?\n";
        std::cout<<"1. Crear Base de datos\n";
        std::cout<<"2. Borrar Base de datos\n";
        std::cout<<"3. Admin. Base de datos\n";
        std::cout<<"4. Leer Base de Datos\n";
        std::cout<<"0. Exit\n";
        std::cin>>value;
        switch(value){
            case 1:
            {
                string tempPath = path;
                int dbSize, blockSize;
                cout<<"Nombre de la base de datos: "<<endl;
                std::cin>>dbName;
                tempPath+=dbName;
                cout<<"Tamano de la base de datos en KB:"<<endl;
                std::cin>>dbSize;
                cout<<"Tamano del bloque en bytes:"<<endl;
                cin>>blockSize;
                char *newPath = new char[tempPath.size()+1];
                copy(tempPath.begin(),tempPath.end(),newPath);
                newPath[tempPath.size()]='\0';
                archivo = new DataFile(newPath);
                archivo->createFile();
                cout<<"Base de datos "<<dbName<<" creada exitosamente"<<endl;
                auto *bm = new BloqueMaestro(dbSize*1024,blockSize);
                bm->Write(archivo);
                TableBlock *tb = new TableBlock(bm->blockSize,bm->firstTableBlock);
                tb->write(archivo);
            }
                break;
            case 2:
            {
                string tempPath = path;
                cout<<"Nombre de la base de datos: ";
                std::cin>>dbName;
                tempPath+=dbName;
                char *newPath = new char[tempPath.size()+1];
                copy(tempPath.begin(),tempPath.end(),newPath);
                newPath[tempPath.size()]='\0';
                cout<<tempPath<<endl;
                if(archivo->deleteFile(newPath) == 0){
                    cout<<"Base de datos "<<dbName<<" borrada exitosamente"<<endl;
                }else{
                    cout<<"No se puedo borrar "<<dbName<<endl;
                }
            }
                break;
            case 3:
            {
                string tempPath = path;
                cout<<"Nombre de la base de datos: \n";
                std::cin>>dbName;
                tempPath+=dbName;
                char *newPath = new char[tempPath.size()+1];
                copy(tempPath.begin(),tempPath.end(),newPath);
                newPath[tempPath.size()]='\0';
                archivo = new DataFile(newPath);
                archivo->openFile();
                BlockManager *blockManager = new BlockManager(archivo);
                bool adminOff=false;
                do{
                    int op=-1;
                    cout<<"Que desea hacer en "<<dbName<<"?\n";
                    cout<<"1. Crear Tabla\n";
                    cout<<"2. Borrar Tabla\n";
                    cout<<"3. Listar Tabla\n";
                    cout<<"0. Salir\n";
                    cin>>op;
                    switch (op){
                        case 1:
                        {
                            string tableName;
                            cout<<"Ingrese nombre tabla: \n";
                            cin>>tableName;
                            char *tname= new char[tableName.size()+1];
                            copy(tableName.begin(),tableName.end(),tname);
                            tname[tableName.size()] ='\0';
                            Table *table = new Table(tname);
                            do{
                                int op2=-1;
                                string temps;
                                cout<<"1. Crear campo int\n";
                                cout<<"2. Crear campo double\n";
                                cout<<"3. Crear campo char\n";
                                cout<<"0. Salir\n";
                                cin>>op2;
                                switch(op2)
                                {
                                    case 1:
                                    {
                                        cout<<"Ingrese nombre del campo: \n";
                                        cin>>temps;
                                        auto fl = new Field(temps,0);
                                        table->Fields->push_back(fl);
                                        break;
                                    }
                                    case 2:
                                    {
                                        cout<<"Ingrese nombre del campo: \n";
                                        cin>>temps;
                                        auto fl = new Field(temps,1);
                                        table->Fields->push_back(fl);
                                        break;
                                    }
                                    case 3:
                                    {
                                        cout<<"Ingrese nombre del campo: \n";
                                        cin>>temps;
                                        auto fl = new Field(temps,2);
                                        table->Fields->push_back(fl);
                                        break;
                                    }
                                    case 0:
                                        break;
                                    default:
                                        cout<<"Ingrese un valor valido!\n";
                                        continue;
                                }
                                table->fieldCount++;
                                cout<<"Ingresar otro campo?\n";
                                cout<<"1. Si\n";
                                cout<<"2. No\n";
                                cin>>op2;
                                if(op2==2){
                                    break;
                                }
                            }while(true);
                            TableBlock *tb = new TableBlock(blockManager->bm->blockSize,blockManager->bm->lastTableBlock);
                            tb->load(archivo);
                            if(tb->fitsTable(table)){
                                tb->tables->push_back(table);
                                tb->tablesCount++;
                                tb->write(archivo);
                            }else{
                                tb = blockManager->asignBlockTable();
                                tb->tables->push_back(table);
                                tb->tablesCount++;
                                tb->write(archivo);
                            }
                        }
                            break;
                        case 2:
                        {
                            string tableName;
                            cout << "Ingrese nombre de la tabla: \n";
                            cin >> tableName;
//                            char *tname= new char[11];
//                            copy(tableName.begin(),tableName.end(),tname);
//                            tname[10] ='\0';
                            int first = blockManager->bm->firstTableBlock;
                            int blockSize= blockManager->bm->blockSize;
                            TableBlock *tb;
                            do{
                                tb = new TableBlock(blockSize,first);
                                tb->load(archivo);
                                if(tb->deleteTable(tableName)){
                                    tb->write(archivo);
                                    cout<<"Se removio la tabla "<<tableName<<endl;
                                    break;
                                }else{
                                    if(tb->nextBlock!=-1){
                                        first = tb->nextBlock;
                                    }else{
                                        cout<<"No se encontro la tabla "<<tableName<<endl;
                                        break;
                                    }
                                }
                            }while(true);
                        }
                            break;
                        case 3:
                        {
                            int first = blockManager->bm->firstTableBlock;
                            int blockSize= blockManager->bm->blockSize;
                            TableBlock *tb;
                            do{
                                tb = new TableBlock(blockSize,first);
                                tb->load(archivo);
                                tb->listTables();
                                first = tb->nextBlock;
                            }while(first!=-1);
                        }
                            break;
                        case 0:
                            adminOff=true;
                            break;
                        default:
                            continue;
                    }
                }while(!adminOff);
            }
                break;
            case 4:
            {
                string tempPath = path;
                cout<<"Nombre de la base de datos: ";
                std::cin>>dbName;
                tempPath+=dbName;
                char *newPath = new char[tempPath.size()+1];
                copy(tempPath.begin(),tempPath.end(),newPath);
                newPath[tempPath.size()]='\0';
                archivo = new DataFile(newPath);
                BloqueMaestro *bm = new BloqueMaestro();
                bm->Load(archivo);
                cout<<bm->blockSize<<bm->blockNumber<<bm->blockNumber<<bm->dbSize<<endl;
                break;
            }
            case 0:
                archivo->closeFile();
                exit=true;
                break;
            default:
                cout<<"Ingrese un valor valido!\n";
                continue;
        }
    }while(!exit);
    return 0;
}