#include "sql/text/grammar_def/result_column.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "sql/text/support/variant_test_visitors.hpp"
#include "test.hpp"

#include <boost/optional/optional_io.hpp>

namespace sql { namespace text {

    using support::variant_type_check_visitor;

    using boost::spirit::x3::forward_ast;

    TEST_CASE( "Empty result column", "[result_column]" ) {
        auto e = parse(result_column, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Empty column wildcard", "[result_column]" ) {
        auto e = parse(result_column_all, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);
    }

    TEST_CASE( "Result column wildcard", "[result_column]" ) {
        auto e = parse(result_column_all, "*");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);
    }

    TEST_CASE( "Empty result column table", "[result_column]" ) {
        auto e = parse(result_column_table, "");

        CHECK( !e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Single char result column table name", "[result_column]" ) {
        auto e = parse(result_column_table, "a.*");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);
        bool schema = boost::apply_visitor( variant_type_check_visitor<ast::schema_table_identifier>(), e.ast.identifier );
        bool simple = boost::apply_visitor( variant_type_check_visitor<ast::simple_table_identifier>(), e.ast.identifier );
        CHECK( !schema );
        CHECK(  simple );
        ast::simple_table_identifier tbl_name = boost::get<ast::simple_table_identifier>(e.ast.identifier);
        CHECK( tbl_name.table.identifier == "a" );
    }

    TEST_CASE( "Empty result column table name", "[result_column]" ) {
        auto e = parse(result_column_table, ".*");

        CHECK( !e.success );
        CHECK( !e.finished );
        CHECK( e.remainder == 2 );
    }

    TEST_CASE( "Simple expression result column", "[result_column]" ) {
        auto e = parse(result_column_expr, "a = b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);

        ast::binary_operation b = boost::get<forward_ast<ast::binary_operation>>(e.ast.expression);

        ast::expr first = b.first;
        ast::expr second = b.second;

        ast::column_identifier cfirst = boost::get<ast::column_identifier>(first);
        ast::column_identifier csecond = boost::get<ast::column_identifier>(second);

        ast::simple_column_identifier sfirst = boost::get<ast::simple_column_identifier>(cfirst);
        ast::simple_column_identifier ssecond = boost::get<ast::simple_column_identifier>(csecond);

        CHECK( sfirst.column.identifier == "a" );
        CHECK( b.op == ast::bop::EQ );
        CHECK( ssecond.column.identifier == "b" );

        CHECK( e.ast.alias == boost::none);
    }

    TEST_CASE( "Aliased expression result column", "[result_column]" ) {
        auto e = parse(result_column_expr, "a = b AS c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);

        ast::binary_operation b = boost::get<forward_ast<ast::binary_operation>>(e.ast.expression);

        ast::expr first = b.first;
        ast::expr second = b.second;

        ast::column_identifier cfirst = boost::get<ast::column_identifier>(first);
        ast::column_identifier csecond = boost::get<ast::column_identifier>(second);

        ast::simple_column_identifier sfirst = boost::get<ast::simple_column_identifier>(cfirst);
        ast::simple_column_identifier ssecond = boost::get<ast::simple_column_identifier>(csecond);

        CHECK( sfirst.column.identifier == "a" );
        CHECK( b.op == ast::bop::EQ );
        CHECK( ssecond.column.identifier == "b" );

        CHECK( e.ast.alias.get().identifier == "c" );
    }

    // Variant tests

    TEST_CASE( "All result column variant", "[result_column]" ) {
        auto e = parse(result_column, "*");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);
        bool al = boost::apply_visitor( variant_type_check_visitor<ast::result_column_all>(), e.ast );
        bool ta = boost::apply_visitor( variant_type_check_visitor<ast::result_column_table>(), e.ast );
        bool ex = boost::apply_visitor( variant_type_check_visitor<ast::result_column_expr>(), e.ast );
        CHECK(  al );
        CHECK( !ta );
        CHECK( !ex );
    }

    TEST_CASE( "Table result columns variant", "[result_column]" ) {
        auto e = parse(result_column, "abc.*");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);
        bool al = boost::apply_visitor( variant_type_check_visitor<ast::result_column_all>(), e.ast );
        bool ta = boost::apply_visitor( variant_type_check_visitor<ast::result_column_table>(), e.ast );
        bool ex = boost::apply_visitor( variant_type_check_visitor<ast::result_column_expr>(), e.ast );
        CHECK( !al );
        CHECK(  ta );
        CHECK( !ex );
    }

    TEST_CASE( "Aliased expression result column variant", "[result_column]" ) {
        auto e = parse(result_column, "a=b AS c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);
        bool al = boost::apply_visitor( variant_type_check_visitor<ast::result_column_all>(), e.ast );
        bool ta = boost::apply_visitor( variant_type_check_visitor<ast::result_column_table>(), e.ast );
        bool ex = boost::apply_visitor( variant_type_check_visitor<ast::result_column_expr>(), e.ast );
        CHECK( !al );
        CHECK( !ta );
        CHECK(  ex );
    }

    TEST_CASE( "Expression result column variant", "[result_column]" ) {
        auto e = parse(result_column, "a=b");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0);
        bool al = boost::apply_visitor( variant_type_check_visitor<ast::result_column_all>(), e.ast );
        bool ta = boost::apply_visitor( variant_type_check_visitor<ast::result_column_table>(), e.ast );
        bool ex = boost::apply_visitor( variant_type_check_visitor<ast::result_column_expr>(), e.ast );
        CHECK( !al );
        CHECK( !ta );
        CHECK(  ex );
    }

    // result column lists
    TEST_CASE( "Result column list: one column", "[result_column]" ) {
        auto e = parse(result_column_list, "\"a\"");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.size() == 1 );
    }

    TEST_CASE( "Result column list: two columns and a binary operation", "[result_column]" ) {
        auto e = parse(result_column_list, "\"a\", [d], b = c");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.size() == 3 );
    }

    TEST_CASE( "Result column list: four columns", "[result_column]" ) {
        auto e = parse(result_column_list, "a, \"b\", [c], `d`");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
        CHECK( e.ast.size() == 4 );
    }

}}
