#include "sql/text/grammar_def/select_core.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Select type: distinct", "[select core]" ) {
        auto e = parse(select_type, "DISTINCT");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select type: all", "[join clause]" ) {
        auto e = parse(select_type, "ALL");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select type: unspecified", "[join clause]" ) {
        auto e = parse(select_type, "");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Simple from clause: one table", "[join clause]" ) {
        auto e = parse(from_clause, "FROM a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Simple from clause: two tables", "[join clause]" ) {
        auto e = parse(from_clause, "FROM a, b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Simple from clause: join", "[join clause]" ) {
        auto e = parse(from_clause, "FROM a JOIN b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Simple group by clause: one column", "[join clause]" ) {
        auto e = parse(groupby_clause, "GROUP BY a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Simple group by clause: two columns", "[join clause]" ) {
        auto e = parse(groupby_clause, "GROUP BY a, b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Group by having clause: two columns, one predicate", "[join clause]" ) {
        auto e = parse(groupby_clause, "GROUP BY a, b HAVING a = 3");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core select: distinct, columns only", "[join clause]" ) {
        auto e = parse(select_core_select, "SELECT DISTINCT a, b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core select: two columns, two tables", "[join clause]" ) {
        auto e = parse(select_core_select, "SELECT a.one, b.two FROM a, b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core select: one column, one join", "[join clause]" ) {
        auto e = parse(select_core_select, "SELECT DISTINCT a.one, b.two FROM a JOIN b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core select: two columns, one predicate", "[join clause]" ) {
        auto e = parse(select_core_select, "SELECT DISTINCT a, b FROM t WHERE a = 3");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select core select: two columns, two predicates", "[join clause]" ) {
        auto e = parse(select_core_select, "SELECT DISTINCT a, b FROM t WHERE a = 3 AND b = 4");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
