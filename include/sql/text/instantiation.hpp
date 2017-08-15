#ifndef SQL_TEXT_INSTANTIATION_HPP
#define SQL_TEXT_INSTANTIATION_HPP

#include "sql/text/parser_def/parse.hpp"

#define INSTANTIATE_TYPE(rule_type)                                            \
    BOOST_SPIRIT_INSTANTIATE(rule_type, iterator_type, context_type);          \
                                                                               \
    template                                                                   \
    parse_result<rule_type::attribute_type>                                    \
    parse<rule_type::id, rule_type::attribute_type>(                           \
        rule_type s,                                                           \
        std::string const& source,                                             \
        std::string input_path);                                               \
    /**/

#define INSTANTIATE(rule)                                                      \
    INSTANTIATE_TYPE(decltype(rule))                                           \
    /**/

#endif //SQL_TEXT_INSTANTIATION_HPP
