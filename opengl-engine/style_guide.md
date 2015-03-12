For all intents and purposes, I try to follow the [Google C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html), unless stated otherwise.

For example, as a header guard I use ```#pragma once ```, instead of ```#ifndef ...```.  
A small example of a class can be seen below:

_.h_
```
#pragma once

#include <string>

namespace something {

class ClassName {

    public:
        ClassName(const int number, const std::string& first_name);

        void func();

        int m_number;
        std::string m_first_name;
};

} // namespace something
```

_.cpp_
```
#include "ClassName.h"
#include <iostream>

namespace something {

ClassName::ClassName(const int number, const std::string& first_name) :
    m_number{number},
    m_first_name{first_name}
{
}

void ClassName::func() {
    const int k_something = 3;
    std::cout << "Something: " << k_something << std::endl;
}

} // namespace something
```
