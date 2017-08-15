#include "sql/text/grammar_def/expr.hpp"
#include "sql/text/grammar_def/select_core.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Function params expr list: non-distinct", "[expr]" ) {
        auto e = parse(function_params_expr_list, "a, b, c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function params expr list: distinct", "[expr]" ) {
        auto e = parse(function_params_expr_list, "DISTINCT a, b, c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function params none", "[expr]" ) {
        auto e = parse(function_params_none, "");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function params row", "[expr]" ) {
        auto e = parse(function_params_row, "*");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function params: expression list, non-distinct", "[expr]" ) {
        auto e = parse(function_params, "a, b, c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function params: expression list, distinct", "[expr]" ) {
        auto e = parse(function_params, "DISTINCT a, b, c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function params: none", "[expr]" ) {
        auto e = parse(function_params, "");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function params: row", "[expr]" ) {
        auto e = parse(function_params, "*");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function call: max on a column", "[expr]" ) {
        auto e = parse(function_call, "max(a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function call: count distinct", "[expr]" ) {
        auto e = parse(function_call, "count(DISTINCT a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function call: count()", "[expr]" ) {
        auto e = parse(function_call, "count()");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Function call: count(*)", "[expr]" ) {
        auto e = parse(function_call, "count(*)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Expr: function call: max on a column", "[expr]" ) {
        auto e = parse(expr, "max(a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Expr: function call: count distinct", "[expr]" ) {
        auto e = parse(expr, "count(DISTINCT a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Expr: function call: count()", "[expr]" ) {
        auto e = parse(expr, "count()");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Expr: function call: count(*)", "[expr]" ) {
        auto e = parse(expr, "count(*)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core: function call: max on a column", "[expr]" ) {
        auto e = parse(select_core, "SELECT max(a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core: function call: count distinct", "[expr]" ) {
        auto e = parse(select_core, "SELECT count(DISTINCT a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core: function call: count()", "[expr]" ) {
        auto e = parse(select_core, "SELECT count()");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core: function call: count(*)", "[expr]" ) {
        auto e = parse(select_core, "SELECT count(*)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
