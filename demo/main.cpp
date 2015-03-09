//
//  main.cpp
//  test
//
//  Created by Clarkok on 15/3/8.
//  Copyright (c) 2015年 Clarkok. All rights reserved.
//

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
