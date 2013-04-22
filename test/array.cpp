#include "../test/tests.h"

#include <csvpp/array.h>

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

void csv::test::array()
{
        {
            // ostream for writing into file
            std::ofstream ofs("foo.csv");
            // csv writer object
            csv::writer writer(ofs);
            for(int i = 0; i < 10; ++i) {
                Foo foo;
                foo.x = i;
                foo.y = 2*i;
                foo.bar = "splash";

                boost::array<Foo, 2> arr;
                arr[0] = foo;
                arr[1] = foo;

                writer << arr << csv::endl;
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
                boost::array<Foo, 2> arr;
                // read from csv and save into console
                parser >> arr >> csv::endl;
                writer << arr << csv::endl;
            }
        }
}
