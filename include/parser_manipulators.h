#ifndef PARSER_MANIPULATORS_H
#define PARSER_MANIPULATORS_H

#include "parser.h"

namespace csv {

inline parser & endl(parser & par)
{
    par._getline();
    return par;
}

}

#endif // PARSER_MANIPULATORS_H
