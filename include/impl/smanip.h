#ifndef SMANIP_H
#define SMANIP_H

namespace csv {

// fwd
class writer;
class parser;

namespace impl {

template< class T >
class smanip : public T
{
public:
    template<class A1>
    explicit smanip(A1 & a1) : T(a1) {}

};

template <class T>
class csmanip : public T
{
public:
    template<class A1>
    explicit csmanip(A1 & a1) : T(a1) {}
};

} // namespace impl
} // namespace csv

#endif // SMANIP_H
