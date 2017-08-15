#ifndef SQL_TEXT_GRAMMAR_SELECT_STMT_HPP
#define SQL_TEXT_GRAMMAR_SELECT_STMT_HPP

#include "sql/fusion/select_stmt.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    // Rule IDs

    struct ordering_term_class;
    struct ordering_term_list_class;
    struct orderby_clause_class;
    struct limit_clause_class;
    struct select_stmt_class;

    // Rules

    const rule<ordering_term_class, ast::ordering_term>
    ordering_term = "ordering_term";

    const rule<ordering_term_list_class, ast::ordering_term_list>
    ordering_term_list = "ordering_term_list";

    const rule<orderby_clause_class, ast::orderby_clause>
    orderby_clause = "orderby_clause";

    const rule<limit_clause_class, ast::limit_clause>
    limit_clause = "limit_clause";

    const rule<select_stmt_class, ast::select_stmt>
    select_stmt = "select_stmt";

}}

#endif //SQL_TEXT_GRAMMAR_SELECT_STMT_HPP
