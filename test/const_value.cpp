#include "../test/tests.h"

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

    Foo(int x, int y, const std::string & bar) :
        x(x), y(y), bar(bar) {}
    Foo() {}
};

void csv::test::const_value()
{
        {
            // ostream for writing into file
            std::ofstream ofs("foo.csv");
            // csv writer object
            csv::writer writer(ofs);
            for(int i = 0; i < 10; ++i) {
                const Foo foo(i, 2*i, "splash");

                writer << foo << csv::endl;
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
                Foo foo;
                // read from csv and save into console
                parser >> foo >> csv::endl;
                writer << foo << csv::endl;
            }
        }
}
