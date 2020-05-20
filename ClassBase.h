#ifndef PROGA_CLASSBASE_H
#define PROGA_CLASSBASE_H


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#define SIGNAL(signalF)((void(*)(string &))(& signalF));
#define HANDLER(handlerF)((void(*)(ClassBase *, string &))(& handlerF));
using namespace std;

class ClassBase {
private:
    vector<ClassBase *> children;
    vector<ClassBase *> :: iterator it_children;

    string name;
    ClassBase *parent;
    int state;
    string message;

    struct objHand{
        int conNum;
        void(*signalMethod)(string &);
        ClassBase * firstClass;
        ClassBase * classOne;
        void(* objHandler)(ClassBase * objSecond, string &);
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
    void (ClassBase::*signal1)(string &) = &ClassBase::signalF;

    //    void (*signal11)(string &) = signal1;

    void handlerF(ClassBase * object, string text);
    void (ClassBase ::* handler1)(ClassBase *, string) = &ClassBase::handlerF;

    void setSignalText(string text);
    string getSignalText();
    void showPath();
    void setConnection(int num, void(* signal)(string &), ClassBase * goalObject, void(* handler)(ClassBase * firstObj, string &));
    void deleteConnection(int num, void(* signal)(string &), ClassBase * goalObject, void(* handler)(ClassBase * firstObj, string &));
    void emitSignals(void(* signal)(string &), string & message);
    void printSignals();

    void printConnectionsAndSignals();
    void printSignalsAll();
};

#endif //PROGA_CLASSBASE_H
