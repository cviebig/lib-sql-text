#include "sql/text/grammar_def/select_stmt.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "No select statement", "[select_stmt]" ) {
        auto e = parse(select_stmt, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "SELECT three columns", "[select_stmt]" ) {
        auto e = parse(select_stmt, "SELECT \"a\", [d], b = c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "SELECT four columns", "[select_stmt]" ) {
        auto e = parse(select_stmt, "SELECT a, \"b\", [c], `d`");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select statement: select, from", "[select_stmt]" ) {
        auto e = parse(select_stmt, "SELECT a FROM b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select statement: select, from, where", "[select_stmt]" ) {
        auto e = parse(select_stmt, "SELECT a FROM b WHERE c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select statement: select, from, where, group by", "[select_stmt]" ) {
        auto e = parse(select_stmt, "SELECT a FROM b WHERE c GROUP BY d");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Select statement: select, from, where, group by, order by", "[select_stmt]" ) {
        auto e = parse(select_stmt, "SELECT a FROM b WHERE c GROUP BY d ORDER BY e");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
