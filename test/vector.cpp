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
};

void csv::test::vector()
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

                std::vector<Foo> vec;
                vec.push_back(foo);
                vec.push_back(foo);

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
