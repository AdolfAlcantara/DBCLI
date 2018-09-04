cmake_minimum_required(VERSION 3.12)
project(DCLI)

set(CMAKE_CXX_STANDARD 14)

add_executable(DCLI main.cpp master/DataFile.cpp master/DataFile.h master/BloqueMaestro.cpp master/BloqueMaestro.h blocks/TableBlock.cpp blocks/TableBlock.h tables/Table.cpp tables/Table.h master/BlockManager.cpp master/BlockManager.h fields/Field.cpp fields/Field.h)