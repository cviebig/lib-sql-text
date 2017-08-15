#ifndef SQL_TEXT_PARSE_HPP
#define SQL_TEXT_PARSE_HPP

#include "sql/text/parser/config.hpp"
#include "sql/text/parser/parse_result.hpp"

#include <boost/spirit/home/x3.hpp>

#include <sstream>
#include <string>

namespace sql { namespace text {

    /* Parse input string using `x3::rule`
     */
    template<typename ID, typename Attribute>
    parse_result<Attribute> parse(boost::spirit::x3::rule<ID, Attribute> rule,
                                  std::string const& source,
                                  std::string input_path = "");

}}

#endif //SQL_TEXT_PARSE_HPP
