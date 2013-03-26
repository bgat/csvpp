#ifndef CSV_IMPL_MACROS_H
#define CSV_IMPL_MACROS_H

#define CSV_MANIPULATORS_FWD()  \
    namespace csv { \
    class writer; \
    writer & endl(writer & wr); \
    class parser; \
    parser & endl(parser & wr); \
    namespace impl { \
    template <class T> class quote_w; \
    template <class T> class iter_w; \
    template <class T> class stream_w; \
    } \
    }

#define CSV_MANIPULATORS_FRIENDS() \
    friend writer & csv::endl(writer &); \
    friend parser & csv::endl(parser &); \
    template <class T> friend class csv::impl::quote_w; \
    template <class T> friend class csv::impl::stream_w; \
    template <class T> friend class csv::impl::iter_w;

#endif // CSV_IMPL_MACROS_H
