#include "tests.h"

int num = 1;

#define CSVPP_TEST(NAME) \
    std::cout << num << ". " << #NAME << std::endl; \
    std::cout << "-----------------------------------" << std::endl; \
    csv::test::NAME(); \
    std::cout << std::endl; \
    num ++;

int main(int /* argc */, char** /* argv */) {

#ifdef NDEBUG
    try {
#endif

        CSVPP_TEST(simple);
        CSVPP_TEST(vector);
        CSVPP_TEST(array);
        CSVPP_TEST(const_value);
        CSVPP_TEST(const_vector);
        CSVPP_TEST(iter);
        CSVPP_TEST(const_iter);
        CSVPP_TEST(iterate);
        CSVPP_TEST(const_iterate);


#ifdef NDEBUG
    } catch(const std::exception & e) {
        std::cout << e.what();
    }
#endif

    return 0;
}

