//
// Created by User on 20.05.2020.
//

#include "ClApp.h"
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"
#include "Class6.h"


//ClApp :: ClApp() {
//    setName("root");
//    setState(1);
//}
ClApp :: ClApp(string name) {
    setName(name);
    setState(1);
}

void ClApp ::buildTree() {
    string name, name1;
    int n, state;
    ClassBase *a, *b;
    cin>>name>>name1>>n>>state;
    while(true){
        if(name == this->getName()) {
            switch (n) {
                case 2:
                    a = new Class2(name1, state, this);
                    break;
                case 3:
                    a = new Class3(name1, state, this);
                    break;
                case 4:
                    a = new Class4(name1, state, this);
                    break;
                case 5:
                    a = new Class5(name1, state, this);
                    break;
                case 6:
                    a = new Class6(name1, state, this);
                    break;
            }
        } else{
            b = this->findObject(name);
            switch(n){
                case 2:
                    a = new Class2(name1, state, b);
                    break;
                case 3:
                    a = new Class3(name1, state, b);
                    break;
                case 4:
                    a = new Class4(name1, state, b);
                    break;
                case 5:
                    a = new Class5(name1, state, b);
                    break;
                case 6:
                    a = new Class6(name1, state, b);
                    break;
            }
        }
        cin>>name;
        if(name == "endtree"){
            return;
        }
        cin>>name1>>n>>state;
    }
}

int ClApp ::exeApp() {
//    showObjectState();
//    showTree();
//    showPath();
    printConnectionsAndSignals();
    showTree();
    printSignalsAll();
    return 0;
}
