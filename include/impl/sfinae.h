#ifndef CSV_SFINAE_H
#define CSV_SFINAE_H

#include <ostream>
#include <istream>

namespace csv {
namespace impl {

typedef char no;
typedef char yes[2];

struct any_t {
    template<class T>
    any_t( T const& );
};

no operator<<( std::ostream const&, any_t const& );
no operator>>( std::istream const&, any_t const& );

template <typename T, typename R>
class has_serialize {
    template<typename U, void (U::*f) (R&, const unsigned int)> struct match;
    template<typename U> static yes &test(match<U, &U::serialize >*);
    template<typename> static no &test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename T, typename R>
class has_csv_serialize {
    template<typename U, void (U::*f) (R&)> struct match;
    template<typename U> static yes &test(match<U, &U::csv_serialize >*);
    template<typename> static no &test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename T, typename R>
class has_save {
    template<typename U, void (U::*f) (R&, const unsigned int) const> struct match;
    template<typename U> static yes &test(match<U, &U::save >*);
    template<typename> static no &test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename T, typename R>
class has_load {
    template<typename U, void (U::*f) (R&, const unsigned int)> struct match;
    template<typename U> static yes &test(match<U, &U::load >*);
    template<typename> static no &test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename T, typename R>
class has_csv_headers {
    template<typename U, void (U::*f) (R&, const unsigned int)> struct match;
    template<typename U> static yes &test(match<U, &U::csv_headers >*);
    template<typename> static no &test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename T, typename R>
class has_const_iterator {
    template <typename U> static yes &test_const_iterator(typename U::const_iterator*);
    template <typename> static no &test_const_iterator(...);
public:
    static const bool value = sizeof(test_const_iterator<T>(0)) == sizeof(yes);
};

template <typename T, typename R>
class has_iterator {
    template <typename U> static yes &test_iterator(typename U::iterator*);
    template <typename> static no &test_iterator(...);
public:
    static const bool value = sizeof(test_iterator<T>(0)) == sizeof(yes);
};

template <typename T, typename R>
class has_insertion_operator {
    static yes& test_insertion_operator( std::ostream& );
    static no test_insertion_operator( no );
    static std::ostream &s;
    static T const &t;
public:
    static bool const value = sizeof( test_insertion_operator(s << t) ) == sizeof( yes );
};

template <typename T, typename R>
class has_extraction_operator {
    static yes& test_extraction_operator( std::istream& );
    static no test_extraction_operator( no );
    static std::istream &s;
    static T const &t;
public:
    static bool const value = sizeof( test_extraction_operator(s >> t) ) == sizeof( yes );
};

} // namespace impl
} // namespace csv

#endif // _SFINAE_H
