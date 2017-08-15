#ifndef SQL_TEXT_GRAMMAR_SELECT_CORE_HPP
#define SQL_TEXT_GRAMMAR_SELECT_CORE_HPP

#include "sql/fusion/select_core.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct select_type_class;
    struct from_clause_class;
    struct groupby_clause_class;
    struct select_core_select_class;
    struct expr_list_list_class;
    struct select_core_values_class;
    struct select_core_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<select_type_class, ast::select_type>
    select_type = "select_type";

    const rule<from_clause_class, ast::from_clause>
    from_clause = "from_clause";

    const rule<groupby_clause_class, ast::groupby_clause>
    groupby_clause = "groupby_clause";

    const rule<select_core_select_class, ast::select_core_select>
    select_core_select = "select_core_select";

    const rule<expr_list_list_class, ast::expr_list_list>
    expr_list_list = "expr_list_list";

    const rule<select_core_values_class, ast::select_core_values>
    select_core_values = "select_core_values";

    const rule<select_core_class, ast::select_core>
    select_core = "select_core";

}}

#endif //SQL_TEXT_GRAMMAR_SELECT_CORE_HPP
