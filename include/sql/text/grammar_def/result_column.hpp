#ifndef SQL_TEXT_GRAMMAR_DEF_RESULT_COLUMN_HPP
#define SQL_TEXT_GRAMMAR_DEF_RESULT_COLUMN_HPP

#include "sql/text/grammar/result_column.hpp"

#include "sql/text/grammar_def/expr.hpp"
#include "sql/text/grammar_def/identifier.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;

    using boost::spirit::x3::ascii::alnum;
    using boost::spirit::x3::ascii::char_;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const result_column_all_def = omit[lit("*")];

    auto const result_column_table_def =
        table_identifier >> lit(".") >> lit("*");

    auto const result_column_expr_def =
        expr >> -(-lit("AS") >> identifier);

    // https://www.sqlite.org/syntax/result-column.html
    //
    auto const result_column_def =
        (
                result_column_all
            |   result_column_table
            |   result_column_expr
        );

    auto const result_column_list_def = result_column % ",";

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( result_column_all )
    BOOST_SPIRIT_DEFINE( result_column_table )
    BOOST_SPIRIT_DEFINE( result_column_expr )
    BOOST_SPIRIT_DEFINE( result_column )
    BOOST_SPIRIT_DEFINE( result_column_list )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct result_column_all_class                    : annotate_on_success {};
    struct result_column_table_class                  : annotate_on_success {};
    struct result_column_expr_class                   : annotate_on_success {};
    struct result_column_class                        : annotate_on_success {};
    struct result_column_list_class                   : annotate_on_success {};

}}

#endif //SQL_TEXT_RESULT_COLUMN_HPP
