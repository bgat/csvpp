#include "../test/tests.h"

#include <csvpp/split_member.h>

class Foo {
public:
    int x;
    int y;
    std::string bar;

    template<class Archive>
    void save(Archive & ar, const unsigned int) const {
        ar & x;
        ar & y;
        ar & bar;
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int) {
        ar & x;
        ar & y;
        ar & bar;
    }

    CSVPP_SPLIT_MEMBER()
};

void csv::test::split_member()
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

