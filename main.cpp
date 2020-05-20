#include <iostream>

#include "ClApp.h"
using namespace std;

int main() {
    string name;
    cin>>name;
    ClApp app(name);

    app.buildTree();

    app.exeApp();

    return 0;
}