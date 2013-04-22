#include "../test/tests.h"

#include <csvpp/vector.h>

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

void csv::test::const_vector()
{
        {
            // ostream for writing into file
            std::ofstream ofs("foo.csv");
            // csv writer object
            csv::writer writer(ofs);
            for(int i = 0; i < 10; ++i) {
                Foo foo(i, 2*i, "splash");
                const std::vector<Foo> vec(2, foo);

                writer << vec << csv::endl;
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
                std::vector<Foo> vec(2);
                // read from csv and save into console
                parser >> vec >> csv::endl;
                writer << vec << csv::endl;
            }
        }
}
