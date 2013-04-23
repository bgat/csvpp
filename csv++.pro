QT       -= core gui

TARGET = csvpp

csvpp_test {
    TEMPLATE = app
    CONFIG += console
    CONFIG -= app_bundle
    CONFIG -= qt
    SOURCES += test/main.cpp \
               test/simple.cpp \
               test/vector.cpp \
               test/array.cpp \
               test/const_value.cpp \
               test/const_vector.cpp \
               test/iter.cpp \
               test/const_iter.cpp \
               test/iterate.cpp \
               test/const_iterate.cpp \
               test/push_line.cpp \
               test/derived_class.cpp \
               test/split_member.cpp
    HEADERS += test/tests.h
} else {
    TEMPLATE = lib
    DEFINES += CSVPP_LIBRARY
}

SOURCES += \
    src/writer.cpp \
    src/parser.cpp

HEADERS += \
    include/csvpp/impl/base.h \
    include/csvpp/impl/smanip.h \
    include/csvpp/impl/macros.h \
    include/csvpp/sfinae/sfinae.h \
    include/csvpp/csv.h \
    include/csvpp/parser.h \
    include/csvpp/writer.h \
    include/csvpp/writer_manipulators.h \
    include/csvpp/parser_manipulators.h \
    include/csvpp/quote.h \
    include/csvpp/iter.h \
    include/csvpp/headers.h \
    include/csvpp/exception.h \
    include/csvpp/vector.h \
    include/csvpp/list.h \
    include/csvpp/impl/containers.h \
    include/csvpp/array.h \
    include/csvpp/set.h \
    include/csvpp/pair.h \
    include/csvpp/map.h \
    include/csvpp/deque.h \
    include/csvpp/sfinae/has_iterator.h \
    include/csvpp/sfinae/has_const_iterator.h \
    include/csvpp/sfinae/has_fcn_serialize.h \
    include/csvpp/sfinae/has_value_type.h \
    include/csvpp/push_line.h \
    include/csvpp/string.h \
    include/csvpp/base_object.h \
    include/csvpp/split_member.h

INCLUDEPATH += $$PWD/include

OTHER_FILES += \
    CMakeLists.txt \
    test/CMakeLists.txt \
    src/CMakeLists.txt
