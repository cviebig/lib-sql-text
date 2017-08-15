#ifndef SQL_TEXT_GRAMMAR_EXPR_HPP
#define SQL_TEXT_GRAMMAR_EXPR_HPP

#include "sql/fusion/expr.hpp"

#include <boost/optional.hpp>
#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct bind_parameter_class;

    struct schema_column_identifier_class;
    struct table_column_identifier_class;
    struct simple_column_identifier_class;
    struct column_identifier_class;

    struct binary_operation_p1_class;
    struct binary_operation_p2_class;
    struct binary_operation_p3_class;
    struct binary_operation_p4_class;
    struct binary_operation_p5_class;
    struct binary_operation_p6_class;
    struct binary_operation_p7_class;
    struct binary_operation_p8_class;

    struct function_params_expr_list_class;
    struct function_params_none_class;
    struct function_params_row_class;
    struct function_params_class;
    struct function_call_class;

    struct expr_class;
    struct expr_list_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<bind_parameter_class, ast::bind_parameter>
    bind_parameter = "bind_parameter";


    const rule<schema_column_identifier_class, ast::schema_column_identifier>
    schema_column_identifier = "schema_column_identifier";

    const rule<table_column_identifier_class, ast::table_column_identifier>
    table_column_identifier = "table_column_identifier";

    const rule<simple_column_identifier_class, ast::simple_column_identifier>
    simple_column_identifier = "simple_column_identifier";


    const rule<function_params_expr_list_class, ast::function_params_expr_list>
    function_params_expr_list = "function_params_expr_list";

    const rule<function_params_none_class, ast::function_params_none>
    function_params_none = "function_params_none";

    const rule<function_params_row_class, ast::function_params_row>
    function_params_row = "function_params_row";

    const rule<function_params_class, ast::function_params>
    function_params = "function_params";

    const rule<function_call_class, ast::function_call>
    function_call = "function_call";


    const rule<column_identifier_class, ast::column_identifier>
    column_identifier = "column_identifier";

    const rule<binary_operation_p1_class, ast::binary_operation>
    binary_operation_p1 = "binary_operation_p1";

    const rule<binary_operation_p2_class, ast::binary_operation>
    binary_operation_p2 = "binary_operation_p2";

    const rule<binary_operation_p3_class, ast::binary_operation>
    binary_operation_p3 = "binary_operation_p3";

    const rule<binary_operation_p4_class, ast::binary_operation>
    binary_operation_p4 = "binary_operation_p4";

    const rule<binary_operation_p5_class, ast::binary_operation>
    binary_operation_p5 = "binary_operation_p5";

    const rule<binary_operation_p6_class, ast::binary_operation>
    binary_operation_p6 = "binary_operation_p6";

    const rule<binary_operation_p7_class, ast::binary_operation>
    binary_operation_p7 = "binary_operation_p7";

    const rule<binary_operation_p8_class, ast::binary_operation>
    binary_operation_p8 = "binary_operation_p8";


    const rule<expr_class, ast::expr>
    expr = "expr";

    const rule<expr_list_class, ast::expr_list>
    expr_list = "expr_list";

}}

#endif //SQL_TEXT_GRAMMAR_EXPR_HPP
