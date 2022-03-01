#include <iostream>
#include <map>

using namespace std;

struct A
{
    virtual void print(){ cout << "A" << endl; }  
};

struct B : public A
{
    virtual void print(){ cout << "B" << endl; }
};

struct C : public A
{
    virtual void print(){ cout << "C" << endl; }
};

std::map<const char*, std::pair<void*, size_t>> vtableMap;

A* createByTypeString(const char* name)
{
    auto& pair = vtableMap[name];
    A* temp = (A*)malloc(pair.second);
    *((void**)temp) = pair.first;
    
    return temp;
}

int main()
{
    {
        A a;
        vtableMap["A"] = { *((void**)&a), sizeof(A) };
        B b;
        vtableMap["B"] = { *((void**)&b), sizeof(B) };
        C c;
        vtableMap["C"] = { *((void**)&c), sizeof(C) };
    }
    
    A* a = createByTypeString("A");
    A* b = createByTypeString("B");
    A* c = createByTypeString("C");
    
    a->print();
    b->print();
    c->print();
    
    cout << "\nCheck dynamic casts\n";
    
    cout << (dynamic_cast<A*>(a) != nullptr) << endl;
    cout << (dynamic_cast<B*>(b) != nullptr) << endl;
    cout << (dynamic_cast<C*>(c) != nullptr) << endl;
    
    return 0;
}
