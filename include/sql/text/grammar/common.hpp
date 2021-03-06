#ifndef SQL_TEXT_GRAMMAR_COMMON_HPP
#define SQL_TEXT_GRAMMAR_COMMON_HPP

#include "sql/fusion/common.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct direction_type_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<direction_type_class, ast::direction_type>
    direction_type = "direction_type";

}}

#endif //SQL_TEXT_GRAMMAR_COMMON_HPP
