//
// Created by User on 20.05.2020.
//

#ifndef PROGA_CLAPP_H
#define PROGA_CLAPP_H

#include "ClassBase.h"

class ClApp : public ClassBase{
public:
    ClApp();
    ClApp(string name);
    void buildTree();
    int exeApp();

};


#endif //PROGA_CLAPP_H
