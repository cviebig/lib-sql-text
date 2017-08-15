#include "sql/text/grammar_def/table_or_subquery.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Table or subquery table with index usage", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_index, "INDEXED BY a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery table without index usage", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_index, "NOT INDEXED");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery table with unspecified index usage", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_index, "");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Non-aliased aliased table identifier", "[table or subquery]" ) {
        auto e = parse(aliased_table_identifier, "a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Aliased table identifier", "[table or subquery]" ) {
        auto e = parse(aliased_table_identifier, "a AS b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery table: aliased, indexed", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_table, "a AS b INDEXED BY c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery table: aliased, not indexed", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_table, "a AS b NOT INDEXED");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }


    TEST_CASE( "Table or subquery table: aliased, index usage unspecified", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_table, "a AS b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery table: non aliased, indexed", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_table, "a INDEXED BY c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery table: non aliased, not indexed", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_table, "a NOT INDEXED");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery table: non aliased, index usage unspecified", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_table, "a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery list", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_list, "a, b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table or subquery sublist", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_sublist, "(a, b)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Empty table or subquery join", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_join, "(a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Empty table or subquery select", "[table or subquery]" ) {
        auto e = parse(table_or_subquery_select, "(SELECT a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
