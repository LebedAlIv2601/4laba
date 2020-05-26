#include <sstream>

#include "ClassBase.h"

ClassBase :: ClassBase(ClassBase *parent) {
    setName("BaseClass");

    if(parent != 0){
        this->parent = parent;
        parent->addChild(this);
    } else {
        this->parent = 0;
    }
}

ClassBase :: ClassBase(string name, int state, ClassBase *parent) {
    setName(name);
    setState(state);

    if(parent != 0){
        this->parent = parent;
        parent->addChild(this);
    } else {
        this->parent = 0;
    }
}

void ClassBase ::setName(string n) {
    name = n;
}

string ClassBase ::getName() {
    return name;
}

void ClassBase ::setParent(ClassBase *parent) {
    if(parent != 0){
        this->parent = parent;
        parent -> children.push_back(this);
    }
}

void ClassBase ::addChild(ClassBase *child) {
    this->children.push_back(child);
}

void ClassBase ::deleteChild(string name) {
    if(children.size() == 0) {
        return;
    }

    it_children = children.begin();

    while(it_children != children.end()){
        if((*it_children)->getName() == name){
            children.erase(it_children);
            return;
        }
        it_children++;
    }
}

ClassBase* ClassBase ::takeChild(string name) {
    ClassBase * child;

    child = getChild(name);

    if(child ==0 ){
        return 0;
    }

    deleteChild(name);
    return child;
}

ClassBase* ClassBase ::getChild(string name) {
    if(children.size() == 0){
        return 0;
    }

    it_children = children.begin();
    while (it_children != children.end()){
        if((*it_children)->getName() == name){
            return *it_children;
        }
        it_children++;
    }
    return 0;
}

void ClassBase ::setState(int state) {
    this->state = state;
}

int ClassBase ::getState() {
    return state;
}

void ClassBase ::showObjectState() {
    cout<<"Test result";
    showNextState((ClassBase *) this);
}
void ClassBase ::showNextState(ClassBase *parent) {
    if(parent -> getState() == 1){
        cout<<endl<< "The object "<<parent->getName()<<" is ready";
    } else {
        cout<<endl<<"The object "<<parent->getName()<<" is not ready";
    }

    if(parent->children.size() == 0){
        return;
    }

    parent -> it_children = parent->children.begin();

    while(parent->it_children != parent ->children.end()){
        showNextState(*(parent->it_children));
        parent->it_children++;
    }
}
ClassBase* ClassBase ::getRoot() {
    ClassBase * parentBefore;

    if(parent == 0){
        return this;
    }

    parentBefore = parent;

    while(parentBefore->parent!=0){
        parentBefore = parentBefore->parent;
    }
    return parentBefore;
}

ClassBase* ClassBase ::findObject(string name) {
    ClassBase * obj = nullptr;
    for(auto e : this->children){
        if(e->getName() == name){
            obj = e;
        }
        if(obj == nullptr){
            obj = e->findObject(name);
        }
    }
    return obj;
}

void ClassBase ::showTree() {
    cout<<"Object tree";
    printTree((ClassBase *) this, 0);
}

void ClassBase ::printTree(ClassBase *parent, int y) {
    cout << endl << string (y, ' ')<< name;
    y+=4;
    for(auto e : this->children){
        e->printTree(e, y);
    }
    if(this->children.empty()){
        return;
    }
}

string ClassBase ::getNameFromPath(string path, int level) {
    int start, end, l;
    l = start = 1;
    while (start != 0){
        end = path.find('/', start);
        if(l == level){
            return path.substr(start, end - start);
        }
        l++;
        start = end+1;
    }
    return "";
}

ClassBase* ClassBase ::getRootPath() {
    ClassBase * parentBefore;
    if(name == "root"){
        return this;
    }

    parentBefore = parent;
    while(parentBefore->parent!=0){
        parentBefore = parentBefore->parent;
    }
    return parentBefore;
}

ClassBase* ClassBase ::findByPath(string path) {
    string p;
    ClassBase * parentNext;
    ClassBase * child;
    int levelNext = 2;

    parentNext = getRootPath();
    p = getNameFromPath(path, 1);
    if(p!="root"){
        return 0;
    }
    p = getNameFromPath(path, levelNext);
    while(!p.empty()){
        child = parentNext->getChild(p);
        if(child!= 0){
            parentNext = child;
            levelNext++;
            p = getNameFromPath(path, levelNext);
        } else{
            return 0;
        }
    }
    return parentNext;
}

string ClassBase ::getPath() {
    stringstream ss;
    if(parent ==0){
        ss <<  "/" << name;
    } else {
        ss << parent->getPath() << "/" << name;
    }
    return ss.str();
}

void ClassBase ::showPath() {
    string a;
    stringstream ss;

    while (true){
        cin >> a;

        if (a == "//"){
            break;
        }

        ss <<"\n";

        ClassBase* component;
        if (a.substr(0,2) == "//") {
            component = this->findObject(a.substr(2));
        } else {
            component = this->findByPath(a);
        }
        if (component != nullptr){
            ss << component->getPath() << " Object name: " << component->getName();
        } else {
            ss << a << " Object not found";
        }

    }
    showTree();
    cout << ss.str();
}

void ClassBase ::setConnection(int num, TYPE_SIGNAL signal, ClassBase * goalObject, TYPE_HANDLER handler) {
    objHand * value;

    if(connections.size()>0){
        for(int i =0; i<connections.size(); i++){
            value = connections.at(i);
            if(value->signalMethod == signal && value->classOne == goalObject && value->objHandler == handler){
                return;
            }
        }
    }
    value = new objHand;
    value->conNum = num;
    value->signalClass = this;
    value->signalMethod = signal;
    value->classOne = goalObject;
    value->objHandler = handler;
    connections.push_back(value);
    getRoot()->globalList.push_back(value);
}

void ClassBase ::deleteConnection(int num, TYPE_SIGNAL signal, ClassBase * goalObject, TYPE_HANDLER handler){
    objHand * value;

    if(connections.size()>0){
        vector<objHand *>::iterator it;
        it=connections.begin();
        for(int i =0; i<connections.size(); i++){
            value = connections.at(i);
            if(value->signalMethod == signal && value->classOne == goalObject && value->objHandler == handler){
                connections.erase(it);
                return;
            }
            it++;
        }
        vector<objHand *>::iterator itGl;
        itGl=getRoot()->connections.begin();
        for(int i =0; i<getRoot()->connections.size(); i++){
            value = getRoot()->connections.at(i);
            if(value->signalMethod == signal && value->classOne == goalObject && value->objHandler == handler){
                getRoot()->connections.erase(itGl);
                return;
            }
            itGl++;
        }
    }
}

void ClassBase ::emitSignals(TYPE_SIGNAL signal, string & message) {
    TYPE_HANDLER handler;
    if(connections.empty()) {
        return;
    }

    CALL_FUNCTION(*this, signal)(message);

    for(int i =0; i<connections.size(); i++){
        if((connections.at(i)->signalMethod)==signal){
            handler = connections.at(i)->objHandler;
            CALL_FUNCTION(*this, handler)(connections.at(i)->classOne, message);
        }
    }
}

void ClassBase ::handlerF(ClassBase * object, string text) {
    cout<<endl<<"Signal to " << object->getName()<< " Text: " << this->getName() <<" -> "<< text;
}

void ClassBase ::signalF(string &) {
    return;
}

void ClassBase ::setSignalText(string text) {
    this->message = text;
}

void ClassBase ::printSignals() {
    if(this->message == ""){
        return;
    } else {
        emitSignals(&ClassBase::signalF, this->message);
    }
}


void ClassBase ::printConnectionsAndSignals() {
    int num;
    string name1, name2;
    ClassBase* b1;
    ClassBase* b2;
    cin>>num;
    while(num!=0){
        cin>>name1;
        if (name1.find("0") != -1){
            break;
        }
        cin>>name2;
        if(name2.find("0") != -1){
            break;
        }
        if (name1 == getRoot()->getName()){
            b2 = getRoot()->findObject(name2);
            getRoot()->setConnection(num, &ClassBase::signalF, b2, &ClassBase::handlerF);
        } else {
            b1 = getRoot()->findObject(name1);
            if(name2 == getRoot()->getName()){
                b1->setConnection(num, &ClassBase::signalF, getRoot(), &ClassBase::handlerF);
            } else {
                b2 = getRoot()->findObject(name2);
                b1->setConnection(num, &ClassBase::signalF, b2, &ClassBase::handlerF);
            }
        }
        cin>>num;
    }
    string text;
    cin>>name1;

    while(name1.find("endsignals") == -1){
        cin>>text;
        if(text.find("endsignals") != -1){
            break;
        }
        if (name1 == getRoot()->getName()){
            getRoot()->setSignalText(text);
            queueMessages.push_back(getRoot());
        }else {
            b1 = getRoot()->findObject(name1);
            b1->setSignalText(text);
            queueMessages.push_back(b1);
        }

        cin>>name1;
    }
}


void ClassBase ::printSignalsAll() {

    cout<<endl<<"Set connects"<<endl;
    for(int k =0; k<getRoot()->globalList.size(); k++){
        cout<<globalList.at(k)->conNum<<" "<<globalList.at(k)->signalClass->getName()<<" "<<globalList.at(k)->classOne->getName()<<endl;
    }
    cout<<"Emit signals";
    for(int k =0; k<getRoot()->queueMessages.size(); k++){
        queueMessages.at(k)->printSignals();
    }
//    printSignals();

}



