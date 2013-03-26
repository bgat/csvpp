#ifndef CSV_PARSER_H
#define CSV_PARSER_H

// STL
#include <istream>
#include <stdexcept>
#include <string>
#include <sstream>

// csv
#include "impl/sfinae.h"
#include "impl/base.h"
#include "impl/smanip.h"
#include "impl/macros.h"

// boost
#include <boost/mpl/if.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

CSV_MANIPULATORS_FWD()

namespace csv {

    class parser : public impl::base {
        CSV_MANIPULATORS_FRIENDS()
    public:
        typedef boost::mpl::bool_<true> is_loading;
        typedef boost::mpl::bool_<false> is_saving;

        parser(std::istream & istream,
               char separator=',',
               char quote='\"',
               char escape='\\');

        template<class T>
        parser &operator>>(T& val) {
            return *this & val;
        }

        template<class T>
        parser &operator&(T& val) {
            typedef typename boost::mpl::if_<
                    impl::has_csv_serialize<T, parser>,
                    parser::csv_serializer,
                    typename boost::mpl::if_<
                    impl::has_serialize<T, parser>,
                    parser::serializer,
                    typename boost::mpl::if_<
                    impl::has_insertion_operator<T, parser>,
                    parser::streamer,
                    typename boost::mpl::if_<
                    impl::has_iterator<T, parser>,
                    parser::iter_serializer,
                    parser::invalid
                    >::type
                    >::type
                    >::type
                    >::type typex;

            BOOST_STATIC_ASSERT(typex::valid); // check if T is possible to read into
            //////////////////////////////////////////////////////////////////////////////
            //                                                                          //
            //   HEY PROGRAMMER, READ THIS !!                                           //
            //                                                                          //
            //   If you see a compilation error here, it means, that you used a type,   //
            //   that is not suitable for loading from csv                              //
            //                                                                          //
            //   Provide a proper serialize() or load() method for this to be working.  //
            //                                                                          //
            //////////////////////////////////////////////////////////////////////////////

            typex::invoke(*this, val);
            return *this;
        }

        template<class T>
        parser &operator&(const T&) {
            BOOST_STATIC_ASSERT(sizeof(T)<0);
            //////////////////////////////////////////////////////////////////////////////
            //                                                                          //
            //   HEY PROGRAMMER, READ THIS !!                                           //
            //                                                                          //
            //   If you see a compilation error here, it means, that you tried to       //
            //   load a csv into const object, which is of course not possible.         //
            //                                                                          //
            //   Check your compiler info to find where this error took place.          //
            //                                                                          //
            //////////////////////////////////////////////////////////////////////////////
            return *this;
        }

        template<class T>
        typename T::parser_ret_type operator&(const impl::smanip<T>& manip) {
            return const_cast<impl::smanip<T>&>(manip)(*this);
        }

        template<class T>
        typename T::parser_ret_type operator&(const impl::csmanip<T>& manip) {
            BOOST_STATIC_ASSERT(sizeof(T)<0);
            //////////////////////////////////////////////////////////////////////////////
            //                                                                          //
            //   HEY PROGRAMMER, READ THIS !!                                           //
            //                                                                          //
            //   If you see a compilation error here, it means, that you tried to       //
            //   load a csv into const object, which is of course not possible.         //
            //                                                                          //
            //   Check your compiler info to find where this error took place.          //
            //                                                                          //
            //////////////////////////////////////////////////////////////////////////////
            return const_cast<impl::csmanip<T>&>(manip)(*this);
        }

        // operatory do manipulatorów
        parser& operator>>(parser& (*pf) (parser&))
        {
            return pf(*this);
        }
        parser& operator&(parser& (*pf) (parser&))
        {
            return pf(*this);
        }

        unsigned line() { return _linenumber; }
        unsigned column() { return _colnumber; }
        bool has_more() {
            if(_iterator != _tokenizer->end())
                return true;
            if(!_empty_istream())
                return true;
            return false;
        }
        bool line_has_more() {
            if(_iterator != _tokenizer->end())
                return true;
            return false;
        }

    private:
        typedef boost::escaped_list_separator<char> list_separator;
        typedef boost::tokenizer<list_separator> tokenizer;
        parser& operator=(const parser&);
        parser(parser&);
        std::istream & _istream;
        unsigned _linenumber;
        unsigned _colnumber;
        list_separator _list_separator;
        tokenizer * _tokenizer;
        tokenizer::iterator _iterator;

        std::string _line;

        bool _empty_istream()
        {
            return std::istream::traits_type::eq_int_type(
                        _istream.rdbuf()->sgetc(),
                        std::istream::traits_type::eof()
                        );
        }

        void _getline();

        struct streamer {
            template<class T>
            static void invoke(parser& par, T& val) {
                if(par._iterator == par._tokenizer->end()) {
                    throw std::runtime_error(
                                "No data available in line " +
                                boost::lexical_cast<std::string>(par._linenumber) +
                                ", column " +
                                boost::lexical_cast<std::string>(par._colnumber)
                                );
                }
                try {
                    val = boost::lexical_cast<T>(*par._iterator);
                } catch (const boost::bad_lexical_cast&) {
                    throw std::runtime_error("Could not interpret data in line " +
                                             boost::lexical_cast<std::string>(par._linenumber) +
                                             ", column " +
                                             boost::lexical_cast<std::string>(par._colnumber));
                }

                ++par._iterator;
                ++par._colnumber;
            }
            static const bool valid = true;
        };

        struct iter_serializer {
            template<class T>
            static void invoke(parser& par, T& val) {
                for(typename T::iterator it = val.begin();
                    it != val.end();
                    ++it)
                {
                    par >> *it;
                }
            }
            static const bool valid = true;
        };

        struct serializer {
            template<class T>
            static void invoke(parser& par, T& val) {
                val.serialize(par, 0);
            }
            static const bool valid = true;
        };

        struct csv_serializer {
            template<class T>
            static void invoke(parser& par, T& val) {
                val.csv_serialize(par);
            }
            static const bool valid = true;
        };

        struct loader {
            template<class T>
            static void invoke(parser& par, T& val) {
                val.load(par, 0);
            }
            static const bool valid = true;
        };

        struct invalid {
            static const bool valid = false;
            template<class T>
            static void invoke(parser& par, const T& val);
        };

        friend struct serializer;
        friend struct streamer;
        friend struct loader;

    };

}

#endif // CSV_PARSER_H
