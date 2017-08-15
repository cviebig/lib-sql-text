#ifndef SQL_TEXT_GRAMMAR_LITERAL_VALUE_HPP
#define SQL_TEXT_GRAMMAR_LITERAL_VALUE_HPP

#include "sql/fusion/literal_value.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct integer_literal_class;
    struct floating_point_literal_class;
    struct numeric_literal_class;
    struct string_literal_class;
    struct null_literal_class;
    struct function_literal_class;
    struct literal_value_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<integer_literal_class, ast::integer_literal>
    integer_literal = "integer_literal";

    const rule<floating_point_literal_class, ast::floating_point_literal>
    floating_point_literal = "floating_point_literal";

    const rule<numeric_literal_class, ast::numeric_literal>
    numeric_literal = "numeric_literal";

    const rule<string_literal_class, ast::string_literal>
    string_literal = "string_literal";

    const rule<null_literal_class, ast::null_literal>
    null_literal = "null_literal";

    const rule<function_literal_class, ast::function_literal>
    function_literal = "function_literal";

    const rule<literal_value_class, ast::literal_value>
    literal_value = "literal_value";

}}

#endif //SQL_TEXT_GRAMMAR_LITERAL_VALUE_HPP
