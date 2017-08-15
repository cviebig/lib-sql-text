#ifndef SQL_TEXT_GRAMMAR_DEF_SELECT_CORE_HPP
#define SQL_TEXT_GRAMMAR_DEF_SELECT_CORE_HPP

#include "sql/text/grammar/select_core.hpp"

#include "sql/text/grammar_def/expr.hpp"
#include "sql/text/grammar_def/result_column.hpp"
#include "sql/text/grammar_def/join_clause.hpp"
#include "sql/text/grammar_def/table_or_subquery.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::lexeme;
    using boost::spirit::x3::matches;
    using boost::spirit::x3::omit;

    using boost::spirit::x3::ascii::alnum;
    using boost::spirit::x3::ascii::alpha;
    using boost::spirit::x3::ascii::char_;
    using boost::spirit::x3::int_;
    using boost::spirit::x3::string;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const select_type_def =
        (
              lit("DISTINCT") >> attr(ast::select_type::distinct)
            | lit("ALL") >> attr(ast::select_type::all)
            | attr(ast::select_type::none)
        );

    auto const from_clause_def =
        omit[lit("FROM")] >>
        (
              &(table_or_subquery >> join_operator) >> join_clause
            | table_or_subquery_list
        );

    auto const groupby_clause_def = lit("GROUP") >> lit("BY") >> expr_list >> -(lit("HAVING") >> expr);

    // TODO: check if there's an ambiguity here
    auto const select_core_select_def =
        lit("SELECT") >> select_type >> result_column_list
        >>  -(from_clause)
        >>  -(lit("WHERE") >> expr)
        >>  -(groupby_clause);

    auto const expr_list_list_def = (lit("(") >> expr_list >> lit(")")) % ',';

    auto const select_core_values_def = expr_list_list;

    // https://www.sqlite.org/syntax/select-core.html
    //
    auto const select_core_def =
        (
              select_core_select
            | select_core_values
        );

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( select_type )
    BOOST_SPIRIT_DEFINE( from_clause )
    BOOST_SPIRIT_DEFINE( groupby_clause )
    BOOST_SPIRIT_DEFINE( select_core_select )
    BOOST_SPIRIT_DEFINE( expr_list_list )
    BOOST_SPIRIT_DEFINE( select_core_values )
    BOOST_SPIRIT_DEFINE( select_core )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct select_type_class                          : annotate_on_success {};
    struct select_core_select_class                   : annotate_on_success {};
    struct expr_list_list_class                       : annotate_on_success {};
    struct select_core_values_class                   : annotate_on_success {};
    struct select_core_class                          : annotate_on_success {};
}}

#endif //SQL_TEXT_GRAMMAR_DEF_SELECT_CORE_HPP
