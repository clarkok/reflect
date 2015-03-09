# Reflect
Complete C++ reflect library in less than 200 lines code.

# Basic Usage
```C++
#include <iostream>
#include "reflect.h"

class Base {
public:
  Base() {
    std::cout << "Base" << std::endl;
  }
};

RE_class(Class1, Base)
{
public:
  Class1() {
    std::cout << "Class1" << std::endl;
  }
};

RE_class(Class2, Base)
{
public:
  Class2() {
    std::cout << "Class2" << std::endl;
  }
};

int main(int argc, const char * argv[]) {
  Reflect(Base)["Class1"]->create();
  return 0;
}
```

And the result:

```
Base
Class1
```

# Document

This library is a header-only library, include the header wherever you need.

This library supports multi-object-file projects, but has no effect on the
efficiency of that program. Neither does this library need a non-standard
preprocessor.

## RE_class(ClassName, BaseClass [, tag])
Defined a class to reflect with in TAG. This macro is to replace 
`class ClassName : public BaseClass`.

## Reflect(BaseClass [, tag])
Return a reference to a `map<string, factory>`, aka. the reflect map.

## tag
A tag is a empty struct that defines a group of reflects, and each group of
reflects will not affect others.
