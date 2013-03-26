#ifndef CSV_WRITER_H
#define CSV_WRITER_H

// STL
#include <ostream>
#include <vector>

// boost
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>

// csv
#include "impl/sfinae.h"
#include "impl/base.h"
#include "impl/smanip.h"
#include "impl/macros.h"

CSV_MANIPULATORS_FWD()

namespace csv {

    class writer : public impl::base {
        CSV_MANIPULATORS_FRIENDS()
    public:
        typedef boost::mpl::bool_<false> is_loading;
        typedef boost::mpl::bool_<true> is_saving;

        writer(std::ostream & ostream,
               char separator=',',
               char quote='\"',
               char escape='\\');

        writer& operator<<(writer& (*pf) (writer&)) { return pf(*this); }
        writer& operator&(writer& (*pf) (writer&)) { return pf(*this); }

        template<class T>
        writer &operator<<(const T& val) {
            return operator &(val);
        }

        template<class T>
        writer &operator&(const T& val) {

            typedef typename boost::mpl::if_<
                    impl::has_csv_serialize<T, writer>,
                    writer::csv_serializer,
                    typename boost::mpl::if_<
                    impl::has_serialize<T, writer>,
                    writer::serializer,
                    typename boost::mpl::if_<
                    impl::has_insertion_operator<T, writer>,
                    writer::streamer,
                    typename boost::mpl::if_<
                    impl::has_const_iterator<T, writer>,
                    writer::iter_serializer,
                    writer::invalid
                    >::type
                    >::type
                    >::type
                    >::type typex;

            //////////////////////////////////////////////////////////////////////////////
            //                                                                          //
            //   HEY PROGRAMMER, READ THIS !!                                           //
            //                                                                          //
            BOOST_STATIC_ASSERT(typex::valid);                                          //
            //                                                                          //
            //   If you see a compilation error here, it means, that you used a type,   //
            //   that is not suitable for writing into csv                              //
            //                                                                          //
            //   Provide a proper serialize() or save() method for this to be working.  //
            //                                                                          //
            //////////////////////////////////////////////////////////////////////////////
            typex::invoke(*this, val);
            return *this;
        }

        template<class T>
        typename T::writer_ret_type operator&(const impl::smanip<T>& manip) {
            return const_cast<impl::smanip<T>&>(manip)(*this);
        }

        template<class T>
        typename T::writer_ret_type operator&(const impl::csmanip<T>& manip) {
            return const_cast<impl::csmanip<T>&>(manip)(*this);
        }

    private:
        writer(const writer&);
        writer& operator=(const writer&);
        std::ostream & _ostream;
        bool _first_in_line;


        struct serializer {
            template<class T>
            static void invoke(writer& wr, const T& val) {
                const_cast<T&>(val).serialize(wr, 0);
            }
            static const bool valid = true;
        };


        struct csv_serializer {
            template<class T>
            static void invoke(writer& wr, const T& val) {
                const_cast<T&>(val).csv_serialize(wr);
            }
            static const bool valid = true;
        };

        struct saver {
            template<class T>
            static void invoke(writer& wr, const T& val) {
                val.save(wr, 0);
            }
            static const bool valid = true;
        };

        struct streamer {
            template<class T>
            static void invoke(writer& wr, const T& val) {
                if(wr._first_in_line) {
                    wr._ostream << val;
                    wr._first_in_line = false;
                    return;
                }
                wr._ostream << wr.separator() << val;
            }
            static const bool valid = true;
        };

        struct iter_serializer {
            template<class T>
            static void invoke(writer& wr, const T& val) {
                for(typename T::const_iterator it = val.begin();
                    it != val.end();
                    ++it)
                {
                    wr << *it;
                }
            }
            static const bool valid = true;
        };

        struct invalid {
            static const bool valid = false;
            template<class T>
            static void invoke(writer& wr, const T& val);
        };

        friend class serializer;
        friend class saver;
        friend class streamer;
        friend class iter_serializer;
    };

}



#endif // CSV_WRITER_H
