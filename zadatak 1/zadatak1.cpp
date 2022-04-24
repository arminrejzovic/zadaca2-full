/*
#include "ArrayList.h"
#include <iostream>

int main(){
    ArrayList<int> a;
    for(int i=1; i<13; i++){
        a.insert(i);
    }
    a.printAll();
    a.removeRange(3,6);
    a.printAll();
    a.removeLast();
    a.printAll();
    cout<<a.getLength()<<endl;

    a.forEach([](int x){
        return x*x;
    });
    a.printAll();
    a.insertAt(0, 99);
    a.printAll();

    cout<<a.at(3)<<endl;
    cout<<a[4]<<endl;

    a.clear();
    a.insert(1);
    a.insert(4);
    a.insert(2);
    a.insert(9);
    a.insert(3);
    a.printAll();
    a.sortItems();
    a.printAll();

    for(const auto& num : a){
        cout<<num<<endl;
    }

    return 0;
}

*/