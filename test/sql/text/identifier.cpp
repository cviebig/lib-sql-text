#include "sql/text/grammar_def/identifier.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    using ast::quot;

    TEST_CASE( "Empty none quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Empty double quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "''");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 2 );
    }

    TEST_CASE( "Empty squared quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "[]");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 2 );
    }

    TEST_CASE( "Empty backtick quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "``");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 2 );
    }



    TEST_CASE( "Single character none quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.identifier == "a" );
        CHECK( e.ast.quotation  == quot::NONE );
    }

    TEST_CASE( "Single character double quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "\"a\"");

        CHECK( e.success   );
        CHECK( e.finished   );
        CHECK( e.remainder == 0   );
        CHECK( e.ast.identifier == "a" );
        CHECK( e.ast.quotation  == quot::DOUBLE           );
    }

    TEST_CASE( "Single character squarly quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "[a]");

        CHECK( e.success    );
        CHECK( e.finished    );
        CHECK( e.remainder == 0    );
        CHECK( e.ast.identifier == "a" );
        CHECK( e.ast.quotation  == quot::SQUARED           );
    }

    TEST_CASE( "Single character backticket quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "`a`");

        CHECK( e.success     );
        CHECK( e.finished     );
        CHECK( e.remainder == 0     );
        CHECK( e.ast.identifier == "a" );
        CHECK( e.ast.quotation  == quot::BACKTICK );
    }

    TEST_CASE( "Single character single quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "'a'");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 3 );
    }



    TEST_CASE( "Single digit none quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "1");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 1 );
    }

    TEST_CASE( "Single digit double quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "\"1\"");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.identifier == "1" );
        CHECK( e.ast.quotation  == quot::DOUBLE );
    }

    TEST_CASE( "Single digit squarly quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "[1]");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.identifier == "1" );
        CHECK( e.ast.quotation  == quot::SQUARED );
    }

    TEST_CASE( "Single digit backticket quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "`1`");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.identifier == "1" );
        CHECK( e.ast.quotation  == quot::BACKTICK );
    }

    TEST_CASE( "Single digit single quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "'1'");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 3 );
    }

    TEST_CASE( "Multiple unquoted words", "[identifier]" ) {
        auto e = parse(identifier, "ab cd");

        CHECK( e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 2 );
    }

    TEST_CASE( "Multiple quoted words", "[identifier]" ) {
        auto e = parse(identifier, "[ab cd]");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 7 );
    }



    TEST_CASE( "Single comma none quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, ",");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 1 );
    }

    TEST_CASE( "Single comma double quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "\",\"");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 3 );
    }

    TEST_CASE( "Single comma squarly quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "[,]");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 3 );
    }

    TEST_CASE( "Single comma backticket quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "`,`");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 3 );
    }

    TEST_CASE( "Single comma single quoted identifier", "[identifier]" ) {
        auto e = parse(identifier, "','");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 3 );
    }


    TEST_CASE( "Comma separated list of single character identifiers", "[identifier]" ) {
        auto e = parse(identifier_list, "a, \"b\", [c], `d`");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.size() == 4 );
        CHECK( e.ast[0].identifier == "a" );
        CHECK( e.ast[1].identifier == "b" );
        CHECK( e.ast[2].identifier == "c" );
        CHECK( e.ast[3].identifier == "d" );
        CHECK( e.ast[0].quotation  == quot::NONE );
        CHECK( e.ast[1].quotation  == quot::DOUBLE );
        CHECK( e.ast[2].quotation  == quot::SQUARED );
        CHECK( e.ast[3].quotation  == quot::BACKTICK );
    }


    TEST_CASE( "Simple table identifier", "[table or subquery]" ) {
        auto e = parse(simple_table_identifier, "a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Schema table identifier", "[table or subquery]" ) {
        auto e = parse(schema_table_identifier, "a.b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table identifier without schema", "[table or subquery]" ) {
        auto e = parse(table_identifier, "a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table identifier with schema", "[table or subquery]" ) {
        auto e = parse(table_identifier, "a.b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
