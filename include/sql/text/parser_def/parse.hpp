/*=============================================================================
  Copyright (c) 2001-2015 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
  =============================================================================*/
#ifndef SQL_TEXT_PARSER_DEF_PARSE_HPP
#define SQL_TEXT_PARSER_DEF_PARSE_HPP

#include "sql/text/parser/parse.hpp"

#include <sstream>
#include <string>

namespace sql { namespace text {

    /* Parse input string using `x3::rule`
     */
    template<typename ID, typename Attribute>
    parse_result<Attribute> parse(boost::spirit::x3::rule<ID, Attribute> rule,
                                  std::string const& source,
                                  std::string input_path) {
        std::stringstream out;
        iterator_type iter(source.cbegin());
        iterator_type const end(source.cend());

        error_handler_type error_handler(iter, end, out, input_path.c_str());

        Attribute attribute;
        bool success =
            phrase_parse(iter, end,
                         boost::spirit::x3::with<
                             boost::spirit::x3::error_handler_tag>(
                                 std::ref(error_handler))[rule],
                         boost::spirit::x3::ascii::space,
                         attribute);

        bool finished = true;
        unsigned int remainder = 0;
        if(iter != end) {
            if(success) {
                error_handler(iter, "Error! Expecting end of input here: ");
            }
            finished = false;
            remainder = end - iter;
        }

        return {success, finished, remainder, attribute, out.str(),
                error_handler};
    };

}}

#endif //SQL_TEXT_PARSER_DEF_PARSE_HPP
