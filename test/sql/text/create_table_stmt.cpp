#include "sql/text/grammar_def/create_table_stmt.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Empty type name", "[expr]" ) {
        auto e = parse(type, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: int", "[expr]" ) {
        auto e = parse(type, "int");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: integer", "[expr]" ) {
        auto e = parse(type, "int");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: float", "[expr]" ) {
        auto e = parse(type, "float");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: text", "[expr]" ) {
        auto e = parse(type, "text");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: INT", "[expr]" ) {
        auto e = parse(type, "INT");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: INTEGER", "[expr]" ) {
        auto e = parse(type, "INTEGER");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: FLOAT", "[expr]" ) {
        auto e = parse(type, "FLOAT");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Identifier: TEXT", "[expr]" ) {
        auto e = parse(type, "TEXT");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Type name: TEXT(1,2)", "[expr]" ) {
        auto e = parse(type_name, "TEXT(1,2)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Type name: TEXT(1)", "[expr]" ) {
        auto e = parse(type_name, "TEXT(1)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Type name: TEXT", "[expr]" ) {
        auto e = parse(type_name, "TEXT");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Empty column def", "[expr]" ) {
        auto e = parse(column_def, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }


    TEST_CASE( "Column definition: a INTEGER", "[expr]" ) {
        auto e = parse(column_def, "a INTEGER");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Column definition list: three int columns", "[expr]" ) {
        auto e = parse(column_def_list, "a INTEGER, b INTEGER, c INTEGER");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Indexed column: direction omitted", "[expr]" ) {
        auto e = parse(indexed_column, "a");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Indexed column: ASC", "[expr]" ) {
        auto e = parse(indexed_column, "a ASC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Indexed column: DESC", "[expr]" ) {
        auto e = parse(indexed_column, "a DESC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Indexed column list: single column, DESC", "[expr]" ) {
        auto e = parse(indexed_column_list, "a DESC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Indexed column list: two columns", "[expr]" ) {
        auto e = parse(indexed_column_list, "a DESC, b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint primary key: keyword only", "[expr]" ) {
        auto e = parse(table_constraint_primary_key, "PRIMARY KEY");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 11 );
    }

    TEST_CASE( "Table constraint unique: keyword only", "[expr]" ) {
        auto e = parse(table_constraint_unique, "UNIQUE");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 6 );
    }

    TEST_CASE( "Table constraint foreign key: keyword only", "[expr]" ) {
        auto e = parse(table_constraint_foreign_key, "FOREIGN KEY");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 11 );
    }

    TEST_CASE( "Table constraint primary key: single column, no direction", "[expr]" ) {
        auto e = parse(table_constraint_primary_key, "PRIMARY KEY (a)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint primary key: single column ASC", "[expr]" ) {
        auto e = parse(table_constraint_primary_key, "PRIMARY KEY (a ASC)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint primary key: single column DESC", "[expr]" ) {
        auto e = parse(table_constraint_primary_key, "PRIMARY KEY (a DESC)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint primary key: two columns", "[expr]" ) {
        auto e = parse(table_constraint_primary_key, "PRIMARY KEY (a ASC, b)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint unique", "[expr]" ) {
        auto e = parse(table_constraint_unique, "UNIQUE (a, b)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint foreign key", "[expr]" ) {
        auto e = parse(table_constraint_foreign_key, "FOREIGN KEY (a, b) REFERENCES c (d, e)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint type: primary key", "[expr]" ) {
        auto e = parse(table_constraint_type, "PRIMARY KEY (a, b)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint type: unique", "[expr]" ) {
        auto e = parse(table_constraint_type, "UNIQUE (a, b)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint type: foreign key", "[expr]" ) {
        auto e = parse(table_constraint_type, "FOREIGN KEY (a, b) REFERENCES c (d, e)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint: primary key", "[expr]" ) {
        auto e = parse(table_constraint, "PRIMARY KEY (a, b)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint: unique", "[expr]" ) {
        auto e = parse(table_constraint, "UNIQUE (a, b)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Table constraint: foreign key", "[expr]" ) {
        auto e = parse(table_constraint, "FOREIGN KEY (a, b) REFERENCES c (d, e)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Named table constraint: primary key", "[expr]" ) {
        auto e = parse(table_constraint, "CONSTRAINT a PRIMARY KEY (b, c)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Named table constraint: unique", "[expr]" ) {
        auto e = parse(table_constraint, "CONSTRAINT a UNIQUE (b, c)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Named table constraint: foreign key", "[expr]" ) {
        auto e = parse(table_constraint, "CONSTRAINT a FOREIGN KEY (b, c) REFERENCES d (e, f)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt columns: three int columns", "[expr]" ) {
        auto e = parse(create_table_stmt_columns, "(a INTEGER, b INTEGER, c INTEGER)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt columns: three int columns, without rowid", "[expr]" ) {
        auto e = parse(create_table_stmt_columns, "(a INTEGER, b INTEGER, c INTEGER) WITHOUT ROWID");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt select: SELECT a FROM b", "[expr]" ) {
        auto e = parse(create_table_stmt_select, "AS SELECT a FROM b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt definition: three int columns, without rowid", "[expr]" ) {
        auto e = parse(create_table_stmt_definition, "(a INTEGER, b INTEGER, c INTEGER) WITHOUT ROWID");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt definition: SELECT a FROM b", "[expr]" ) {
        auto e = parse(create_table_stmt_definition, "AS SELECT a FROM b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt: persistent", "[expr]" ) {
        auto e = parse(create_table_stmt, "CREATE TABLE a (b INT)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt: persistent, schema", "[expr]" ) {
        auto e = parse(create_table_stmt, "CREATE TABLE s.a (b INT)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt: persistent, two columns, foreign key", "[expr]" ) {
        auto e = parse(create_table_stmt, "CREATE TABLE a (b INT, c INT, FOREIGN KEY (b, c) REFERENCES d (e, f))");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt: temp", "[expr]" ) {
        auto e = parse(create_table_stmt, "CREATE TEMP TABLE a (b INT)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt: temporary", "[expr]" ) {
        auto e = parse(create_table_stmt, "CREATE TEMPORARY TABLE a (b INT)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }


    TEST_CASE( "Create table stmt: if not exists", "[expr]" ) {
        auto e = parse(create_table_stmt, "CREATE TABLE IF NOT EXISTS a (b INT)");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Create table stmt: select", "[expr]" ) {
        auto e = parse(create_table_stmt, "CREATE TABLE c AS SELECT a FROM b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
