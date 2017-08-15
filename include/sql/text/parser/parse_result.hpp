#ifndef SQL_TEXT_PARSER_PARSE_RESULT_HPP
#define SQL_TEXT_PARSER_PARSE_RESULT_HPP

#include "sql/text/parser/config.hpp"

#include <sstream>
#include <string>

namespace sql { namespace text {

    template<typename Attribute>
    struct parse_result {
        /* Indicates whether parsing was successful
         */
        bool success;

        /* Indicates whether the whole input string was consumed by the parser
         */
        bool finished;

        /* The number of characters that remain unparsed
         */
        unsigned int remainder;

        /* Parsed attribute
         */
        Attribute attribute;

        /* Diagnostic messages
         */
        std::string messages;

        /* Errors
         */
        error_handler_type errors;

        /* Parse result
         */
        parse_result(bool success, bool finished,
                     unsigned int remainder, Attribute attribute,
                     std::string messages,
                     error_handler_type errors)
            : success(success), finished(finished), remainder(remainder),
              attribute(attribute), messages(messages), errors(errors) {}
    };

}}

#endif //SQL_TEXT_PARSER_PARSE_RESULT_HPP
