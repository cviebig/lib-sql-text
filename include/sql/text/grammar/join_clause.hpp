#ifndef SQL_TEXT_GRAMMAR_JOIN_CLAUSE_HPP
#define SQL_TEXT_GRAMMAR_JOIN_CLAUSE_HPP

#include "sql/fusion/join_clause.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct join_operator_type_class;
    struct join_operator_class;
    struct join_constraint_expr_class;
    struct join_constraint_columns_class;
    struct join_constraint_omitted_class;
    struct join_constraint_class;
    struct join_class;
    struct join_list_class;
    struct join_clause_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<join_operator_type_class, ast::join_operator_type>
    join_operator_type = "join_operator_type";

    const rule<join_operator_class, ast::join_operator>
    join_operator = "join_operator";

    const rule<join_constraint_expr_class, ast::join_constraint_expr>
    join_constraint_expr = "join_constraint_expr";

    const rule<join_constraint_columns_class, ast::join_constraint_columns>
    join_constraint_columns = "join_constraint_columns";

    const rule<join_constraint_omitted_class, ast::join_constraint_omitted>
    join_constraint_omitted = "join_constraint_omitted";

    const rule<join_constraint_class, ast::join_constraint>
    join_constraint = "join_constraint";

    const rule<join_class, ast::join>
    join = "join";

    const rule<join_list_class, ast::join_list>
    join_list = "join_list";

    const rule<join_clause_class, ast::join_clause>
    join_clause = "join_clause";

}}

#endif //SQL_TEXT_GRAMMAR_JOIN_CLAUSE_HPP
