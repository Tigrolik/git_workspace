#ifndef _MY_FACILITIES_H_
#define _MY_FACILITIES_H_

#include <iostream>
#include <stdexcept>

using namespace std;

void error(const string &s) {
    throw runtime_error(s);
}

#endif

