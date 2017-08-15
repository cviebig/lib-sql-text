#include "sql/text/grammar_def/join_clause.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Join operator type: LEFT OUTER", "[join clause]" ) {
        auto e = parse(join_operator_type, "LEFT OUTER");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join operator type: LEFT", "[join clause]" ) {
        auto e = parse(join_operator_type, "LEFT");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join operator type: INNER", "[join clause]" ) {
        auto e = parse(join_operator_type, "INNER");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Natural join operator", "[join clause]" ) {
        auto e = parse(join_operator, "NATURAL LEFT JOIN");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Non-natural join operator", "[join clause]" ) {
        auto e = parse(join_operator, "LEFT JOIN");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join constraint expression", "[join clause]" ) {
        auto e = parse(join_constraint_expr, "ON a = b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }


    TEST_CASE( "Join constraint columns", "[join clause]" ) {
        auto e = parse(join_constraint_columns, "USING (a, b, c)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join constraint as expression", "[join clause]" ) {
        auto e = parse(join_constraint, "ON a = b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }


    TEST_CASE( "Join constraint as list of columns", "[join clause]" ) {
        auto e = parse(join_constraint, "USING (a, b, c)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    // Dependency on table_or_subquery
    TEST_CASE( "Join", "[join clause]" ) {
        auto e = parse(join, "LEFT OUTER JOIN b ON a.a = b.a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Empty join list", "[join clause]" ) {
        auto e = parse(join_list, "");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Simple join list", "[join clause]" ) {
        auto e = parse(join_list, "JOIN b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join list: single item", "[join clause]" ) {
        auto e = parse(join_list, "LEFT OUTER JOIN b ON a.a = b.a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join list: two items", "[join clause]" ) {
        auto e = parse(join_list, "LEFT OUTER JOIN b ON a.a = b.a JOIN c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join clause: one join", "[join clause]" ) {
        auto e = parse(join_clause, "a JOIN b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Join clause: two joins", "[join clause]" ) {
        auto e = parse(join_clause, "a LEFT OUTER JOIN b ON a.a = b.a JOIN c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
