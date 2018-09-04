//
// Created by FuryCoder on 3/9/2018.
//

#include "Field.h"

Field::Field(string fieldName,int dataType) {
    int actualSize = fieldName.size()+1;
    this->fieldName = new char[actualSize];
    copy(fieldName.begin(),fieldName.end(),this->fieldName);
    this->fieldName[fieldName.size()] = '\0';
    this->size = actualSize;
    this->dataType = dataType;
}
