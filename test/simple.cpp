#include "../test/tests.h"

void csv::test::simple()
{
    {
       // ostream for writing into file
        std::ofstream ofs("foo.csv");
        // csv writer object
        csv::writer writer(ofs);
        for(int i = 0; i < 10; ++i) {
            int x = i;
            int y = 2*i;
            std::string z = "splash";

            writer << x << y << z << csv::endl;
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
            int x;
            int y;
            std::string z;


            // read from csv and save into console
            parser >> x >> y >> z >> csv::endl;
            writer << x << y << z << csv::endl;
        }
    }
}
