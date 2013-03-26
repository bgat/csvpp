QT       -= core gui

TARGET = csv
TEMPLATE = lib

DEFINES += CSV_LIBRARY

SOURCES += \
    src/writer.cpp \
    src/parser.cpp

HEADERS += \
    include/impl/sfinae.h \
    include/impl/base.h \
    include/impl/smanip.h \
    include/impl/macros.h \
    include/impl/operator.h \
    include/csv.h \
    include/parser.h \
    include/writer.h \
    include/writer_manipulators.h \
    include/parser_manipulators.h \
    include/quote.h \
    include/iter.h \
    include/stream.h \
    include/headers.h

INCLUDEPATH += $$PWD/include
