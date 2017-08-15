#include "sql/text/grammar_def/sql_stmt.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Select statement", "[sql_stmt]" ) {
        auto e = parse(sql_stmt, "SELECT a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table statement", "[sql_stmt]" ) {
        auto e = parse(sql_stmt, "CREATE TABLE a (b INT)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table statement", "[sql_stmt]" ) {
        auto e = parse(sql_stmt, "IMPORT TABLE a FROM CSV FILE a.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
