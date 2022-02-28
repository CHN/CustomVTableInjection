# Custom VTable Injection

```cpp
#include <iostream>

using namespace std;

struct A
{
    int x = 1;
    virtual void abc(int b){cout << x * b;}  
};

struct B : public A
{
    int y = 2;
    virtual void abc(int b){cout << y * b;}
};

int main()
{
    void* t = malloc(16);
    *(((int*)t)+3) = 6;
    
    *(void**)t = (void*)new void*();
    void** v = (void**)*(void**)(t);
    *v = (void*)&B::abc;
    
    A* a = (A*)t;
    
    a->abc(2);
    
    free(t);
    
    return 0;
}
```

# Create Polymorphic object from string
```cpp
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
    
    return 0;
}
```
