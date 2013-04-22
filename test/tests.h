#ifndef CSVPP_TESTS_H
#define CSVPP_TESTS_H

// stl
#include <iostream>
#include <fstream>

// csv++
#include <csvpp/csv.h>
#include <csvpp/string.h>

namespace csv {
namespace test {

void simple();
void vector();
void array();
void quote();
void iter();
void serialization();
void const_value();
void const_vector();
void iter();
void const_iter();
void iterate();
void const_iterate();

}
}

#endif
