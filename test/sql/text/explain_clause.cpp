#include "sql/text/grammar_def/sql_stmt.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Empty explain clause", "[explain clause]" ) {
        auto e = parse(explain_clause, "");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( !e.ast.explain );
        CHECK( !e.ast.query_plan );
    }

    TEST_CASE( "EXPLAIN", "[explain clause]" ) {
        auto e = parse(explain_clause, "EXPLAIN");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.explain );
        CHECK( !e.ast.query_plan );
    }

    TEST_CASE( "EXPLAIN QUERY PLAN", "[explain clause]" ) {
        auto e = parse(explain_clause, "EXPLAIN QUERY PLAN");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.explain );
        CHECK( e.ast.query_plan );
    }

    TEST_CASE( "Incomplete query plan", "[explain clause]" ) {
        auto e = parse(explain_clause, "EXPLAIN QUER");

        CHECK( e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 4 );
        CHECK( e.ast.explain );
        CHECK( !e.ast.query_plan );
    }

    TEST_CASE( "Incomplete explain", "[explain clause]" ) {
        auto e = parse(explain_clause, "EXPLAI");

        CHECK( e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 6 );
        CHECK( !e.ast.explain );
        CHECK( !e.ast.query_plan );
    }

}}
