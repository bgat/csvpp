#ifndef CSVPP_PUSH_LINE_H
#define CSVPP_PUSH_LINE_H

// csv++
#include <csvpp/parser.h>
#include <csvpp/sfinae/has_value_type.h>
#include <csvpp/impl/smanip.h>

// boost
#include <boost/type_traits/is_const.hpp>

namespace csv {

// fwd
namespace impl {
template <class T> class push_line_w;
}
template <class T> impl::smanip< impl::push_line_w<T> > push_line(T &);

namespace impl {

template <class T>
class push_line_w {
    friend impl::smanip< impl::push_line_w<T> > push_line<T>(T &);
    friend class smanip<push_line_w<T> >;
    friend class csmanip<push_line_w<T> >;
public:
    typedef void writer_ret_type;
    typedef void parser_ret_type;

    parser_ret_type operator()(parser & par)
    {
        //////////////////////////////////////////////////////////////////////////////
        //                                                                          //
        //   HEY PROGRAMMER, READ THIS !!                                           //
        //                                                                          //
        BOOST_STATIC_ASSERT(sfinae::has_value_type<T>::value);
        //                                                                          //
        //   If you see a compilation error here, it means, that you tried to       //
        //   use csv::push_back with class that does not have a value_type          //
        //   nested type. If you want to provide your own container to be working   //
        //   with csv++ library you need to specify value_type.                     //
        //                                                                          //
        //   Check your compiler info to find where this error took place.          //
        //                                                                          //
        //////////////////////////////////////////////////////////////////////////////

        while(par.more_in_line()) {
            //////////////////////////////////////////////////////////////////////////////
            //                                                                          //
            //   HEY PROGRAMMER, READ THIS !!                                           //
            //                                                                          //
            typename T::value_type t;
            //                                                                          //
            //   If you see a compilation error here, it means, that you tried to       //
            //   use csv::push_back with class that does not have a default             //
            //   constructor. If you want to use this class T with csv::push_back, you  //
            //   you need to provide default constructor                                //
            //                                                                          //
            //   Check your compiler info to find where this error took place.          //
            //                                                                          //
            //////////////////////////////////////////////////////////////////////////////

            par >> t;

            //////////////////////////////////////////////////////////////////////////////
            //                                                                          //
            //   HEY PROGRAMMER, READ THIS !!                                           //
            //                                                                          //
            _wrapped.push_back(t);
            //                                                                          //
            //   If you see a compilation error here, it means, that you tried to       //
            //   use csv::push_back with class that does not have a push_back method    //
            //   If you want to provide your own container to be working                //
            //   with csv++ library you need to specify push_back.                      //
            //                                                                          //
            //   Check your compiler info to find where this error took place.          //
            //                                                                          //
            //////////////////////////////////////////////////////////////////////////////
        }
        par >> csv::endl;
    }

    template<class Archive>
    void serialize(Archive &, const unsigned int)
    {
        //////////////////////////////////////////////////////////////////////////////
        //                                                                          //
        //   HEY PROGRAMMER, READ THIS !!                                           //
        //                                                                          //
        BOOST_STATIC_ASSERT(sizeof(Archive)<0);                                     //
        //                                                                          //
        //   If you see a compilation error here, it means, that you tried to       //
        //   use csv::push_back with class other than csv::parser.                  //
        //   csv::push_back is compatibile with csv::parser only!                   //
        //                                                                          //
        //   Check your compiler info to find where this error took place.          //
        //                                                                          //
        //////////////////////////////////////////////////////////////////////////////
    }

private:
    push_line_w(const push_line_w&);
    push_line_w & operator=(const push_line_w &);
    explicit push_line_w(T & wrapped) :
        _wrapped(wrapped)
    {
        //////////////////////////////////////////////////////////////////////////////
        //                                                                          //
        //   HEY PROGRAMMER, READ THIS !!                                           //
        //                                                                          //
        BOOST_STATIC_ASSERT(!boost::is_const<T>::value);                            //
        //                                                                          //
        //   If you see a compilation error here, it means, that you tried to       //
        //   load csv into const object.                                            //
        //                                                                          //
        //   Check your compiler info to find where this error took place.          //
        //                                                                          //
        //////////////////////////////////////////////////////////////////////////////
    }
    T & _wrapped;
};

} // namespace impl

template <class T>
impl::smanip< impl::push_line_w<T> > push_line(T & wrapped)
{
    return impl::smanip< impl::push_line_w<T> >((T&)wrapped);
}

template <class T>
impl::csmanip< impl::push_line_w<T> > push_line(const T & wrapped)
{
    return impl::csmanip< impl::push_line_w<T> >(wrapped);
}


} // namespace csv

#endif // CSVPP_PUSH_LINE_H
