#ifndef PROGA_CLASSBASE_H
#define PROGA_CLASSBASE_H


#include <iostream>
#include <string>
#include <vector>


using namespace std;

class ClassBase {
    typedef void(ClassBase:: * TYPE_SIGNAL)(string &);
    typedef void(ClassBase:: * TYPE_HANDLER)(ClassBase *,string);
#define CALL_FUNCTION(obj,ptrToFunction)  ((obj).*(ptrToFunction))
private:
    vector<ClassBase *> children;
    vector<ClassBase *> :: iterator it_children;

    string name;
    ClassBase *parent;
    int state;
    string message = "";

    struct objHand{
        int conNum;
        ClassBase * signalClass;
        TYPE_SIGNAL signalMethod;
        ClassBase * classOne;
        TYPE_HANDLER objHandler;
    };

    vector<objHand *> connections;
    vector<objHand *> globalList;

    ClassBase * getRoot();
    void showNextState (ClassBase * parent);
    void printTree(ClassBase * parent, int y);


public:
    ClassBase(ClassBase * parent = 0);
    ClassBase(string name, int state, ClassBase * parent);

    void setName(string n);
    string getName();

    void setParent(ClassBase * parent);
    void addChild(ClassBase * child);
    void deleteChild(string name);
    ClassBase * takeChild (string name);
    ClassBase * getChild (string name);

    void setState(int state);
    int getState();

    void showObjectState();
    void showTree();

    ClassBase * findObject(string name);
    string getNameFromPath(string path, int level);
    string getPath();
    ClassBase * getRootPath();
    ClassBase * findByPath(string path);
    void signalF(string &);
    void handlerF(ClassBase *, string text);
    void setSignalText(string text);
    void showPath();
    void setConnection(int num, TYPE_SIGNAL signal, ClassBase * goalObject, TYPE_HANDLER handler);
    void deleteConnection(int num, TYPE_SIGNAL signal, ClassBase * goalObject, TYPE_HANDLER handler);
    void emitSignals(TYPE_SIGNAL signal, string & message);
    void printSignals();

    void printConnectionsAndSignals();
    void printSignalsAll();
};

#endif //PROGA_CLASSBASE_H
