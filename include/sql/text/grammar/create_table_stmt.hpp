#ifndef SQL_TEXT_GRAMMAR_CREATE_TABLE_STMT_HPP
#define SQL_TEXT_GRAMMAR_CREATE_TABLE_STMT_HPP

#include "sql/fusion/create_table_stmt.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct type_class;
    struct type_name_bounded_class;
    struct type_name_upper_bounded_class;
    struct type_name_unbounded_class;
    struct type_name_class;
    struct column_def_class;
    struct column_def_list_class;
    struct indexed_column_class;
    struct indexed_column_list_class;
    struct table_constraint_primary_key_class;
    struct table_constraint_unique_class;
    struct table_constraint_foreign_key_class;
    struct table_constraint_type_class;
    struct table_constraint_class;
    struct table_constraint_list_class;
    struct create_table_stmt_columns_class;
    struct create_table_stmt_select_class;
    struct create_table_stmt_definition_class;
    struct create_table_stmt_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<type_class, std::string>
    type = "type";

    const rule<type_name_bounded_class, ast::type_name>
    type_name_bounded = "type_name_bounded";

    const rule<type_name_upper_bounded_class, ast::type_name>
    type_name_upper_bounded = "type_name_upper_bounded";

    const rule<type_name_unbounded_class, ast::type_name>
    type_name_unbounded = "type_name_unbounded";

    const rule<type_name_class, ast::type_name>
    type_name = "type_name";

    const rule<column_def_class, ast::column_def>
    column_def = "column_def";

    const rule<column_def_list_class, ast::column_def_list>
    column_def_list = "column_def_list";



    const rule<indexed_column_class, ast::indexed_column>
    indexed_column = "indexed_column";

    const rule<indexed_column_list_class, ast::indexed_column_list>
    indexed_column_list = "indexed_column_list";

    const rule<table_constraint_primary_key_class,
               ast::table_constraint_primary_key>
    table_constraint_primary_key = "table_constraint_primary_key";

    const rule<table_constraint_unique_class, ast::table_constraint_unique>
    table_constraint_unique = "table_constraint_unique";

    const rule<table_constraint_foreign_key_class,
               ast::table_constraint_foreign_key>
    table_constraint_foreign_key = "table_constraint_foreign_key";

    const rule<table_constraint_type_class, ast::table_constraint_type>
    table_constraint_type = "table_constraint_type";

    const rule<table_constraint_class, ast::table_constraint>
    table_constraint = "table_constraint";

    const rule<table_constraint_list_class, ast::table_constraint_list>
    table_constraint_list = "table_constraint_list";



    const rule<create_table_stmt_columns_class, ast::create_table_stmt_columns>
    create_table_stmt_columns = "create_table_stmt_columns";

    const rule<create_table_stmt_select_class, ast::create_table_stmt_select>
    create_table_stmt_select = "create_table_stmt_select";

    const rule<create_table_stmt_definition_class,
               ast::create_table_stmt_definition>
    create_table_stmt_definition = "create_table_stmt_definition";

    const rule<create_table_stmt_class, ast::create_table_stmt>
    create_table_stmt = "create_table_stmt";

}}

#endif //SQL_TEXT_GRAMMAR_CREATE_TABLE_STMT_HPP
