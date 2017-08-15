#ifndef SQL_TEXT_GRAMMAR_DEF_JOIN_CLAUSE_HPP
#define SQL_TEXT_GRAMMAR_DEF_JOIN_CLAUSE_HPP

#include "sql/text/grammar/join_clause.hpp"

#include "sql/text/grammar_def/expr.hpp"
#include "sql/text/grammar_def/identifier.hpp"
#include "sql/text/grammar_def/table_or_subquery.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/support/unused.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::omit;
    using boost::spirit::x3::unused;

    using boost::spirit::x3::ascii::char_;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    // https://www.sqlite.org/syntax/join-operator.html
    //
    auto const join_operator_type_def =
        (
              omit[lit("LEFT")] >> omit[lit("OUTER")] >> attr(ast::join_operator_type::left_outer)
            | omit[lit("LEFT")] >> attr(ast::join_operator_type::left)
            | omit[lit("INNER")] >> attr(ast::join_operator_type::inner)
            | omit[lit("CROSS")] >> attr(ast::join_operator_type::cross)
            | attr(ast::join_operator_type::plain)
        );

    auto const join_operator_def =
        (omit[lit("NATURAL")] >> attr(true) | attr(false))
        >> join_operator_type
        >> lit("JOIN");

    // https://www.sqlite.org/syntax/join-constraint.html
    //
    auto const join_constraint_expr_def = lit("ON") >> expr;

    auto const join_constraint_columns_def =
        lit("USING") >> lit("(") >> identifier_list >> lit(")");

    auto const join_constraint_omitted_def = attr(unused);

    auto const join_constraint_def =
        (
              join_constraint_expr
            | join_constraint_columns
            | join_constraint_omitted
        );

    auto const join_def = join_operator >> table_or_subquery >> join_constraint;

    auto const join_list_def = *join;

    auto const join_clause_def = table_or_subquery >> join_list;

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( join_operator_type )
    BOOST_SPIRIT_DEFINE( join_operator )
    BOOST_SPIRIT_DEFINE( join_constraint_expr )
    BOOST_SPIRIT_DEFINE( join_constraint_columns )
    BOOST_SPIRIT_DEFINE( join_constraint_omitted )
    BOOST_SPIRIT_DEFINE( join_constraint )
    BOOST_SPIRIT_DEFINE( join )
    BOOST_SPIRIT_DEFINE( join_list )
    BOOST_SPIRIT_DEFINE( join_clause )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct join_operator_type_class                   : annotate_on_success {};
    struct join_operator_class                        : annotate_on_success {};
    struct join_constraint_expr_class                 : annotate_on_success {};
    struct join_constraint_columns_class              : annotate_on_success {};
    struct join_constraint_omitted_class              : annotate_on_success {};
    struct join_constraint_class                      : annotate_on_success {};
    struct join_class                                 : annotate_on_success {};
    struct join_list_class                            : annotate_on_success {};
    struct join_clause_class                          : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_JOIN_CLAUSE_HPP
