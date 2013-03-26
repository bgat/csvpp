#ifndef CSV_ITER_H
#define CSV_ITER_H

#include "writer.h"
#include "parser.h"
#include "impl/smanip.h"

namespace csv {

namespace impl {
template <class T>
class iter_w {
    friend class smanip<iter_w>;
    friend class csmanip<iter_w>;
public:
    typedef parser& parser_ret_type;
    typedef writer& writer_ret_type;
    writer& operator()(writer & wr)
    {
        typedef typename impl::has_const_iterator<T, writer> typex;

        //////////////////////////////////////////////////////////////////////////////
        //                                                                          //
        //   HEY PROGRAMMER, READ THIS !!                                           //
        //                                                                          //
        BOOST_STATIC_ASSERT(typex::value);                                          //
        //                                                                          //
        //   If you see a compilation error here, it means, that you used a type,   //
        //   that is not suitable for writing into csv                              //
        //                                                                          //
        //   Provide a proper serialize() or save() method for this to be working.  //
        //                                                                          //
        //////////////////////////////////////////////////////////////////////////////

        // invoke the iterator_serializer
        writer::iter_serializer::invoke(wr, _wrapped);
        return wr;
    }
    parser& operator()(parser & par)
    {
        typedef typename impl::has_iterator<T, writer> typex;

        //////////////////////////////////////////////////////////////////////////////
        //                                                                          //
        //   HEY PROGRAMMER, READ THIS !!                                           //
        //                                                                          //
        BOOST_STATIC_ASSERT(typex::value);                                         //
        //                                                                          //
        //   If you see a compilation error here, it means, that you used a type,   //
        //   that is not suitable for writing into csv                              //
        //                                                                          //
        //   Provide a proper serialize() or save() method for this to be working.  //
        //                                                                          //
        //////////////////////////////////////////////////////////////////////////////

        parser::iter_serializer::invoke(par, _wrapped);
        return par;
    }

private:
    iter_w(const iter_w&);
    iter_w & operator=(const iter_w &);
    iter_w(T & wrapped) :
        _wrapped(wrapped)
    {}
    iter_w(const T & wrapped) :
        _wrapped(const_cast<T&>(wrapped))
    {}
    T & _wrapped;
};

} // namespace impl

template <class T>
impl::smanip< impl::iter_w<T> > iter(T & wrapped)
{
    return impl::smanip< impl::iter_w<T> >(wrapped);
}

template <class T>
const impl::csmanip< impl::iter_w<T> > iter(const T & wrapped)
{
    return impl::csmanip< impl::iter_w<T> >(wrapped);
}

} // namespace csv


#endif // CSV_ITER_H
