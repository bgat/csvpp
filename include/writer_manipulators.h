#ifndef WRITER_MANIPULATORS_H
#define WRITER_MANIPULATORS_H

#include "writer.h"

namespace csv {

inline writer & endl(writer & wr)
{
    wr._ostream << std::endl;
    wr._first_in_line = true;
    return wr;
}

}

#endif // WRITER_MANIPULATORS_H
