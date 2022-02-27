# CustomVTableInjection

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
    
    *(unsigned long int**)(t) = (unsigned long int*)new void*();
    void** v = (void**)*(unsigned long int**)(t);
    *v = (unsigned long int*)(void*)&B::abc;
    
    A* a = (A*)t;
    a->abc(2);
    
    free(t);
    
    return 0;
}
```
