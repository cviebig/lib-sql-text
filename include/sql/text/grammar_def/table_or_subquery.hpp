#ifndef SQL_TEXT_GRAMMAR_DEF_TABLE_OR_SUBQUERY_HPP
#define SQL_TEXT_GRAMMAR_DEF_TABLE_OR_SUBQUERY_HPP

#include "sql/text/grammar/table_or_subquery.hpp"

#include "sql/text/grammar_def/expr.hpp"
#include "sql/text/grammar_def/identifier.hpp"
#include "sql/text/grammar_def/join_clause.hpp"
#include "sql/text/grammar_def/select_stmt.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::omit;

    using boost::spirit::x3::ascii::char_;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const table_or_subquery_index_yes_def =
        omit[lit("INDEXED")] >> omit[lit("BY")]
        >> identifier
        >> attr(ast::index_usage_type::yes);

    boost::optional<ast::identifier> const empty_identifier;

    auto const table_or_subquery_index_no_def  =
        omit[lit("NOT")] >> omit[lit("INDEXED")]
        >> attr(empty_identifier)
        >> attr(ast::index_usage_type::no);

    auto const table_or_subquery_index_unspecified_def =
        attr(empty_identifier)
        >> attr(ast::index_usage_type::not_specified);

    auto const table_or_subquery_index_def =
        (
              table_or_subquery_index_yes_def
            | table_or_subquery_index_no_def
            | table_or_subquery_index_unspecified_def
        );

    auto const table_or_subquery_table_def =
        aliased_table_identifier >> table_or_subquery_index;

    auto const table_or_subquery_sublist_def =
        lit("(") >> table_or_subquery_list >> lit(")");

    auto const table_or_subquery_join_def =
        lit("(") >> join_clause >> lit(")");

    auto const table_or_subquery_select_def =
        lit("(") >> select_stmt >> lit(")")
        >>  -(-lit("AS") >> identifier);

    // https://www.sqlite.org/syntax/table-or-subquery.html
    //
    auto const table_or_subquery_def =
        (
              table_or_subquery_table
            // | table_or_subquery_function
            | table_or_subquery_sublist
            | table_or_subquery_join
            | table_or_subquery_select
        );

    auto const table_or_subquery_list_def = table_or_subquery % ',';

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( table_or_subquery_index )
    BOOST_SPIRIT_DEFINE( table_or_subquery_table )
    BOOST_SPIRIT_DEFINE( table_or_subquery_sublist )
    BOOST_SPIRIT_DEFINE( table_or_subquery_join )
    BOOST_SPIRIT_DEFINE( table_or_subquery_select )
    BOOST_SPIRIT_DEFINE( table_or_subquery )
    BOOST_SPIRIT_DEFINE( table_or_subquery_list )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct table_or_subquery_index_class              : annotate_on_success {};
    struct table_or_subquery_table_class              : annotate_on_success {};
    struct table_or_subquery_sublist_class            : annotate_on_success {};
    struct table_or_subquery_join_class               : annotate_on_success {};
    struct table_or_subquery_select_class             : annotate_on_success {};
    struct table_or_subquery_class                    : annotate_on_success {};
    struct table_or_subquery_list_class               : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_TABLE_OR_SUBQUERY_HPP
