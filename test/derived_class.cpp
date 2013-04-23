#include "../test/tests.h"

#include <csvpp/base_object.h>

class Foo {
public:
    int x;
    int y;
    std::string bar;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & x;
        ar & y;
        ar & bar;
    }
};

class Bar : public Foo {
public:
    int z;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & csv::base_object<Foo>(*this);
        ar & z;
    }
};

void csv::test::derived_class()
{
    {
        // ostream for writing into file
        std::ofstream ofs("foo.csv");
        // csv writer object
        csv::writer writer(ofs);
        for(int i = 0; i < 10; ++i) {
            Bar boo;
            boo.x = i;
            boo.y = 2*i;
            boo.z = i+3;
            boo.bar = "splash";

            writer << boo << csv::endl;
        }
    }
    {
        // istream for reading from file
        std::ifstream ifs("foo.csv");
        // parser object
        csv::parser parser(ifs);
        // console writer can be used to display csv
        csv::writer writer(std::cout);
        while(parser.more()) {
            Bar boo;
            // read from csv and save into console
            parser >> boo >> csv::endl;
            writer << boo << csv::endl;
        }
    }
}

