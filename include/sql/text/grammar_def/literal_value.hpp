#ifndef SQL_TEXT_GRAMMAR_DEF_LITERAL_VALUE_HPP
#define SQL_TEXT_GRAMMAR_DEF_LITERAL_VALUE_HPP

#include "sql/text/grammar/literal_value.hpp"

#include "sql/text/grammar_def/reserved_words.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using ast::quot;

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::omit;

    using boost::spirit::x3::ascii::alnum;
    using boost::spirit::x3::int_;
    using boost::spirit::x3::float_;
    using boost::spirit::x3::print;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    // https://www.sqlite.org/syntax/literal-value.html
    //
    auto const integer_literal_def = int_;

    auto const floating_point_literal_def = float_;

    auto const numeric_literal_def =
        (
              floating_point_literal
            | integer_literal
        );

    auto const string_literal_def =
        lit("'") >> *(print - "'") >> lit("'")
        >>  attr(quot::SINGLE);

    auto const null_literal_def = omit[lit("NULL")];

    auto const function_literal_def =
        (
              omit[lit("CURRENT_DATE")]
              >> attr(ast::fun_type::current_date)
            | omit[lit("CURRENT_TIMESTAMP")]
              >> attr(ast::fun_type::current_timestamp)
            | omit[lit("CURRENT_TIME")]
              >> attr(ast::fun_type::current_time)
        );

    auto const literal_value_def =
        (
              numeric_literal
            | string_literal
            | null_literal
            | function_literal
        );

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( string_literal )
    BOOST_SPIRIT_DEFINE( integer_literal )
    BOOST_SPIRIT_DEFINE( floating_point_literal )
    BOOST_SPIRIT_DEFINE( numeric_literal )
    BOOST_SPIRIT_DEFINE( null_literal )
    BOOST_SPIRIT_DEFINE( function_literal )
    BOOST_SPIRIT_DEFINE( literal_value )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct integer_literal_class                      : annotate_on_success {};
    struct floating_point_literal_class               : annotate_on_success {};
    struct numeric_literal_class                      : annotate_on_success {};
    struct string_literal_class                       : annotate_on_success {};
    struct null_literal_class                         : annotate_on_success {};
    struct function_literal_class                     : annotate_on_success {};
    struct literal_value_class                        : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_LITERAL_VALUE_HPP
