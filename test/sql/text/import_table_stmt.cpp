#include "sql/text/grammar_def/import_table_stmt.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Import table source csv: missing file name", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 8 );
    }

    TEST_CASE( "Import table source csv: file name, without delimited by clause", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE name.tbl");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 17 );
    }

    TEST_CASE( "Import table source csv: file name, without delimiter", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE name.tbl DELIMITED BY");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 30 );
    }

    TEST_CASE( "Import table source csv: file name, delimited by commas", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE name.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table source csv: file name, delimited by commas (2)", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE name.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table source csv: relative path (UNIX)", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE ../data/name.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table source csv: absolute path (UNIX)", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE /home/user/data/name.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table source csv: relative path (Microsoft Windows)", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE ..\\data\\name.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table source csv: absolute path (Microsoft Windows)", "[import_table_stmt]" ) {
        auto e = parse(import_table_source_csv, "CSV FILE C:\\users\\data\\name.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table source: csv", "[import_table_stmt]" ) {
        auto e = parse(import_table_source, "CSV FILE name.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table: no schema, csv ", "[import_table_stmt]" ) {
        auto e = parse(import_table_stmt, "IMPORT TABLE a FROM CSV FILE a.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Import table: schema, csv ", "[import_table_stmt]" ) {
        auto e = parse(import_table_stmt, "IMPORT TABLE demo.a FROM CSV FILE a.tbl DELIMITED BY ','");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
