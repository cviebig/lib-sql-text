#ifndef SQL_TEXT_GRAMMAR_RESULT_COLUMN_HPP
#define SQL_TEXT_GRAMMAR_RESULT_COLUMN_HPP

#include "sql/fusion/result_column.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct result_column_all_class;
    struct result_column_table_class;
    struct result_column_expr_class;
    struct result_column_class;
    struct result_column_list_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<result_column_all_class, ast::result_column_all>
    result_column_all = "result_column_all";

    const rule<result_column_table_class, ast::result_column_table>
    result_column_table = "result_column_table";

    const rule<result_column_expr_class, ast::result_column_expr>
    result_column_expr = "result_column_expr";

    const rule<result_column_class, ast::result_column>
    result_column = "result_column";

    const rule<result_column_list_class, ast::result_column_list>
    result_column_list = "result_column_list";

}}

#endif //SQL_TEXT_RESULT_COLUMN_HPP
