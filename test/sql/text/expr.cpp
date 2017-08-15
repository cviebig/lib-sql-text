#include "sql/text/grammar_def/expr.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Empty expression", "[expr]" ) {
        auto e = parse(expr, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "bind-parameter", "[expr]" ) {
        auto e = parse(bind_parameter, "?");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Schema column identifier", "[expr]" ) {
        auto e = parse(schema_column_identifier, "a.a.a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Tale column identifier", "[expr]" ) {
        auto e = parse(table_column_identifier, "a.a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Simple column identifier", "[expr]" ) {
        auto e = parse(simple_column_identifier, "a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Literal Literal Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "1=1");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Literal Bind-Value Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "1=?");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Literal Column Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "1=a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Bind-Value Literal Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "?=1");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Bind-Value Bind-Value Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "?=?");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Bind-Value Column Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "?=a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Column Literal Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "a=1");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Column Bind-Value Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "a=?");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Column Column Binary operation", "[expr]" ) {
        auto e = parse(binary_operation, "a=a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Column Column Binary operation Expression", "[expr]" ) {
        auto e = parse(expr, "a = b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Binary operation expression: (a * b) + (c * d)", "[expr]" ) {
        auto e = parse(expr, "a * b + c * d");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Binary operation expression: mult, add, braces", "[expr]" ) {
        auto e = parse(expr, "(a * b) + (c * d)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Binary operation expression: OR, AND, braces", "[expr]" ) {
        auto e = parse(expr, "(a OR b) AND (c OR d)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
