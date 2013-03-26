#ifndef CSV_QUOTE_H
#define CSV_QUOTE_H

#include "writer.h"
#include "parser.h"
#include "impl/smanip.h"

namespace csv {

namespace impl {
template <class T>
class quote_w {
    friend class smanip<quote_w>;
    friend class csmanip<quote_w>;
public:
    typedef parser& parser_ret_type;
    typedef writer& writer_ret_type;
    writer& operator()(writer & wr)
    {
        if(wr._first_in_line) {
            wr._ostream << wr.quote_char() << _wrapped << wr.quote_char();
            wr._first_in_line = false;
            return wr;
        }
        wr._ostream << wr.separator() << wr.quote_char() << _wrapped << wr.quote_char();
        return wr;
    }
    parser& operator()(parser & par)
    {
        parser::streamer::invoke(par, _wrapped);
        return par;
    }

private:
    quote_w(const quote_w&);
    quote_w & operator=(const quote_w &);
    explicit quote_w(T & wrapped) :
        _wrapped(wrapped)
    {}
    explicit quote_w(const T & wrapped) :
        _wrapped(const_cast<T&>(wrapped))
    {}
    T & _wrapped;
};

} // namespace impl

template <class T>
impl::smanip< impl::quote_w<T> > quote(T & wrapped)
{
    return impl::smanip< impl::quote_w<T> >(wrapped);
}

template <class T>
const impl::csmanip< impl::quote_w<T> > quote(const T & wrapped)
{
    return impl::csmanip< impl::quote_w<T> >(wrapped);
}

} // namespace csv

#endif // CSV_QUOTE_H
