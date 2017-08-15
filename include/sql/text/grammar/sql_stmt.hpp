#ifndef SQL_TEXT_GRAMMAR_SQL_STMT_HPP
#define SQL_TEXT_GRAMMAR_SQL_STMT_HPP

#include "sql/fusion/sql_stmt.hpp"

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct explain_clause_class;
    struct sql_stmt_class;
    struct sql_stmt_list_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<explain_clause_class, ast::explain_clause>
    explain_clause = "explain_clause";

    const rule<sql_stmt_class, ast::sql_stmt>
    sql_stmt = "sql_stmt";

    const rule<sql_stmt_list_class, ast::sql_stmt_list>
    sql_stmt_list = "sql_stmt_list";

}}

#endif //SQL_TEXT_GRAMMAR_SQL_STMT_HPP
