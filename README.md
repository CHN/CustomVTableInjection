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
    A* t = (A*)malloc(16);
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
