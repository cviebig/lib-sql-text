#include "sql/text/grammar_def/literal_value.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "sql/text/support/variant_test_visitors.hpp"
#include "test.hpp"

namespace sql { namespace text {

    using ast::fun_type;

    using ast::quot;

    using support::variant_type_check_visitor;

    TEST_CASE( "No string literal", "[literal_value]" ) {
        auto e = parse(string_literal, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "No numeric literal", "[literal_value]" ) {
        auto e = parse(numeric_literal, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "No NULL literal", "[literal_value]" ) {
        auto e = parse(null_literal, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "No function literal", "[literal_value]" ) {
        auto e = parse(function_literal, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "No literal value", "[literal_value]" ) {
        auto e = parse(null_literal, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }


    TEST_CASE( "Integer numeric literal", "[literal_value]" ) {
        auto e = parse(numeric_literal, "300");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "Floating point numeric literal", "[literal_value]" ) {
        auto e = parse(numeric_literal, "3.14159");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }


    TEST_CASE( "Empty string literal", "[literal_value]" ) {
        auto e = parse(string_literal, "''");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Single character string literal", "[literal_value]" ) {
        auto e = parse(string_literal, "'a'");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        CHECK( e.attribute.literal == "a" );
        CHECK( e.attribute.quotation  == quot::SINGLE );
    }

    TEST_CASE( "Single digit string literal", "[literal_value]" ) {
        auto e = parse(string_literal, "'1'");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        CHECK( e.attribute.literal    == "1" );
        CHECK( e.attribute.quotation  == quot::SINGLE );
    }

    TEST_CASE( "Single quoted comma string literal", "[literal_value]" ) {
        auto e = parse(string_literal, "','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }


    TEST_CASE( "NULL literal", "[literal_value]" ) {
        auto e = parse(null_literal, "NULL");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "CURRENT_DATE function literal", "[literal_value]" ) {
        auto e = parse(function_literal, "CURRENT_DATE");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "CURRENT_TIME function literal", "[literal_value]" ) {
        auto e = parse(function_literal, "CURRENT_TIME");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    TEST_CASE( "CURRENT_TIMESTAMP function literal", "[literal_value]" ) {
        auto e = parse(function_literal, "CURRENT_TIMESTAMP");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
    }

    // Variant tests
    TEST_CASE( "Integer numeric literal variant", "[literal_value]" ) {
        auto e = parse(literal_value, "5");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        bool v = boost::apply_visitor( variant_type_check_visitor<ast::numeric_literal>(), e.attribute );
        CHECK( v );
    }

    TEST_CASE( "Floating point numeric literal variant", "[literal_value]" ) {
        auto e = parse(literal_value, "2.71828");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        bool v = boost::apply_visitor( variant_type_check_visitor<ast::numeric_literal>(), e.attribute );
        CHECK( v );
    }

    TEST_CASE( "String literal variant", "[literal_value]" ) {
        auto e = parse(literal_value, "'Earth'");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        bool v = boost::apply_visitor( variant_type_check_visitor<ast::string_literal>(), e.attribute );
        CHECK( v );
    }

    TEST_CASE( "NULL literal variant", "[literal_value]" ) {
        auto e = parse(literal_value, "NULL");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        bool v = boost::apply_visitor( variant_type_check_visitor<ast::null_literal>(), e.attribute );
        CHECK( v );
    }

    TEST_CASE( "CURRENT_DATE function literal variant", "[literal_value]" ) {
        auto e = parse(literal_value, "CURRENT_DATE");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        bool v = boost::apply_visitor( variant_type_check_visitor<ast::function_literal>(), e.attribute );
        CHECK( v );
    }

    TEST_CASE( "CURRENT_TIME function literal variant", "[literal_value]" ) {
        auto e = parse(literal_value, "CURRENT_TIME");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        bool v = boost::apply_visitor( variant_type_check_visitor<ast::function_literal>(), e.attribute );
        CHECK( v );
    }

    TEST_CASE( "CURRENT_TIMESTAMP function literal variant", "[literal_value]" ) {
        auto e = parse(literal_value, "CURRENT_TIMESTAMP");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder  == 0 );
        bool v = boost::apply_visitor( variant_type_check_visitor<ast::function_literal>(), e.attribute );
        CHECK( v );
    }

}}
