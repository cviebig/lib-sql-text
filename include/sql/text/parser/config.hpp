/*=============================================================================
  Copyright (c) 2001-2015 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
  =============================================================================*/
#ifndef SQL_TEXT_PARSER_CONFIG_HPP
#define SQL_TEXT_PARSER_CONFIG_HPP

#include "sql/text/parser/error_handler.hpp"

#include <boost/spirit/home/x3.hpp>

#include <string>

namespace sql { namespace text {

    // Our Iterator Type
    using iterator_type = std::string::const_iterator;

    // Our Error Handler
    using error_handler_type = boost::spirit::x3::error_handler<iterator_type>;

    // Combined Error Handler and Phrase Parse Context
    //
    // Definition differs between Boost version < 1.67 and >= 1.67 due to
    // breaking change:
    // https://www.boost.org/users/history/version_1_67_0.html
    // https://github.com/boostorg/spirit/pull/239
    // https://github.com/boostorg/spirit/pull/254
#if BOOST_VERSION >= 106700
    using context_type =
        boost::spirit::x3::context<
            boost::spirit::x3::error_handler_tag,
            std::reference_wrapper<error_handler_type> const,
            boost::spirit::x3::phrase_parse_context<
                boost::spirit::x3::ascii::space_type
            >::type
        >;
#else
    using context_type =
        boost::spirit::x3::with_context<
            boost::spirit::x3::error_handler_tag,
            std::reference_wrapper<error_handler_type> const,
            boost::spirit::x3::phrase_parse_context<
                boost::spirit::x3::ascii::space_type
            >::type
        >::type;
#endif
}}

#endif //SQL_TEXT_PARSER_CONFIG_HPP
