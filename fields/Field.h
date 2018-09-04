//
// Created by FuryCoder on 3/9/2018.
//

#ifndef DCLI_FIELD_H
#define DCLI_FIELD_H

#include <string>

using namespace std;

class Field {

public:
    Field(string fieldName, int dataType);
    char *fieldName;
    int dataType;
    int size;
};

/*El datatype sera:
 *  1 = int
 *  2 = double
 *  3 = string*/

#endif //DCLI_FIELD_H
