#ifndef SQL_TEXT_GRAMMAR_TABLE_OR_SUBQUERY_HPP
#define SQL_TEXT_GRAMMAR_TABLE_OR_SUBQUERY_HPP

#include "sql/fusion/table_or_subquery.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct table_or_subquery_index_class;
    struct table_or_subquery_table_class;
    struct table_or_subquery_sublist_class;
    struct table_or_subquery_join_class;
    struct table_or_subquery_select_class;
    struct table_or_subquery_class;
    struct table_or_subquery_list_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<table_or_subquery_index_class, ast::table_or_subquery_index>
    table_or_subquery_index = "table_or_subquery_index";

    const rule<table_or_subquery_table_class, ast::table_or_subquery_table>
    table_or_subquery_table = "table_or_subquery_table";

    const rule<table_or_subquery_sublist_class, ast::table_or_subquery_sublist>
    table_or_subquery_sublist = "table_or_subquery_sublist";

    const rule<table_or_subquery_join_class, ast::table_or_subquery_join>
    table_or_subquery_join = "table_or_subquery_join";

    const rule<table_or_subquery_list_class, ast::table_or_subquery_list>
    table_or_subquery_list = "table_or_subquery_list";

    const rule<table_or_subquery_select_class, ast::table_or_subquery_select>
    table_or_subquery_select = "table_or_subquery_select";

    const rule<table_or_subquery_class, ast::table_or_subquery>
    table_or_subquery = "table_or_subquery";

}}

#endif //SQL_TEXT_GRAMMAR_TABLE_OR_SUBQUERY_HPP
