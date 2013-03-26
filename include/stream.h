#ifndef CSV_STREAM_H
#define CSV_STREAM_H

#include "writer.h"
#include "parser.h"
#include "impl/smanip.h"

namespace csv {

namespace impl {

template <class T>
class stream_w {
    friend class smanip<stream_w>;
    friend class csmanip<stream_w>;
public:
    typedef parser& parser_ret_type;
    typedef writer& writer_ret_type;
    writer& operator()(writer & wr)
    {
        typedef typename impl::has_insertion_operator<T, writer> typex;

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
        writer::streamer::invoke(wr, _wrapped);
        return wr;
    }
    parser& operator()(parser & par)
    {
        typedef typename impl::has_extraction_operator<T, writer> typex;

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
        parser::streamer::invoke(par, _wrapped);
        return par;
    }

private:
    stream_w(const stream_w&);
    stream_w & operator=(const stream_w &);
    stream_w(T & wrapped) :
        _wrapped(wrapped)
    {}
    stream_w(const T & wrapped) :
        _wrapped(const_cast<T&>(wrapped))
    {}
    T & _wrapped;
};

} // namespace impl

template <class T>
impl::smanip< impl::stream_w<T> > stream(T & wrapped)
{
    return impl::smanip< impl::stream_w<T> >(wrapped);
}

template <class T>
const impl::csmanip< impl::stream_w<T> > stream(const T & wrapped)
{
    return impl::csmanip< impl::stream_w<T> >(wrapped);
}

} // namespace csv

#endif // CSV_STREAM_H
