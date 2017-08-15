/*=============================================================================
    Copyright (c) 2001-2015 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SQL_TEXT_PARSER_ERROR_HANDLER_HPP
#define SQL_TEXT_PARSER_ERROR_HANDLER_HPP

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

namespace sql { namespace text {

    struct error_handler_base {

        template <typename Iterator, typename Exception, typename Context>
        boost::spirit::x3::error_handler_result
        on_error(Iterator& first, Iterator const& last, Exception const& x,
                 Context const& context) {
            auto& error_handler =
                boost::spirit::x3::get<boost::spirit::x3::error_handler_tag>
                    (context).get();
            error_handler(x.where(),
                          "Error! Expecting: " + x.which() + " here:");
            return boost::spirit::x3::error_handler_result::fail;
        }

    };

}}

#endif //SQL_TEXT_PARSER_ERROR_HANDLER_HPP
