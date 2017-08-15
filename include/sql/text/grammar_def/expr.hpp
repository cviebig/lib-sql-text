#ifndef SQL_TEXT_GRAMMAR_DEF_EXPR_HPP
#define SQL_TEXT_GRAMMAR_DEF_EXPR_HPP

#include "sql/text/grammar/expr.hpp"

#include "sql/text/grammar_def/identifier.hpp"
#include "sql/text/grammar_def/literal_value.hpp"

#include <boost/optional.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/support/unused.hpp>

namespace sql { namespace text {

    using ast::bop;

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::omit;
    using boost::spirit::x3::unused;

    using boost::spirit::x3::ascii::char_;


    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const bind_parameter_def = omit[lit("?")];


    auto const schema_column_identifier_def =
        identifier >> lit(".") >> identifier >> lit(".") >> identifier;

    auto const table_column_identifier_def =
        identifier >> lit(".") >> identifier;

    auto const simple_column_identifier_def =
        identifier;

    auto const column_identifier_def =
        (
              schema_column_identifier
            | table_column_identifier
            | simple_column_identifier
        );


    auto const function_params_expr_list_def =
        (omit[lit("DISTINCT")] >> attr(true) | attr(false))
        >> expr_list;

    auto const function_params_none_def = attr(unused);

    auto const function_params_row_def = omit[char_('*')];

    auto const function_params_def =
        (
              function_params_expr_list
            | function_params_row
            | function_params_none
        );

    auto const function_call_def =
        identifier >> omit[char_('(')] >> function_params >> omit[char_(')')];


    auto const binary_operator_p1 =
        omit[lit("||")] >> attr(ast::bop::CAT);

    auto const binary_operator_p2 =
          omit[char_('*')] >> attr(ast::bop::MUL)
        | omit[char_('/')] >> attr(ast::bop::DIV)
        | omit[char_('%')] >> attr(ast::bop::MOD);

    auto const binary_operator_p3 =
          omit[char_('+')] >> attr(ast::bop::ADD)
        | omit[char_('-')] >> attr(ast::bop::SUB);

    auto const binary_operator_p4 =
          omit[lit(">>")] >> attr(ast::bop::BSR)
        | omit[lit("<<")] >> attr(ast::bop::BSL)
        | omit[char_('&')] >> attr(ast::bop::BAND)
        | omit[char_('|')] >> attr(ast::bop::BOR);

    auto const binary_operator_p5 =
          omit[lit("<=")] >> attr(ast::bop::LE)
        | omit[char_('<')] >> attr(ast::bop::LT)
        | omit[lit(">=")] >> attr(ast::bop::GE)
        | omit[char_(">")] >> attr(ast::bop::GT)
        | omit[char_('=')] >> attr(ast::bop::EQ)
        | omit[lit("==")] >> attr(ast::bop::EQQ)
        | omit[lit("!=")] >> attr(ast::bop::NE)
        | omit[lit("<>")] >> attr(ast::bop::NEE)
        | omit[lit("IS NOT ")] >> attr(ast::bop::ISNOT);

    auto const binary_operator_p6 =
          omit[lit("IS ")] >> attr(ast::bop::IS)
        | omit[lit("IN ")] >> attr(ast::bop::IN)
        | omit[lit("LIKE ")] >> attr(ast::bop::LIKE)
        | omit[lit("GLOB ")] >> attr(ast::bop::GLOB)
        | omit[lit("MATCH ")] >> attr(ast::bop::MATCH)
        | omit[lit("REGEXPR ")] >> attr(ast::bop::REGEXP);

    auto const binary_operator_p7 =
        omit[lit("AND ")] >> attr(ast::bop::AND);

    auto const binary_operator_p8 =
        omit[lit("OR ")] >> attr(ast::bop::OR);

    // Avoids left recursion in binary_operation (expr >> .. >> expr)
    auto const expr_left_def =
        (
              omit[char_('(')] >> expr >> omit[char_(')')]
            | literal_value
            | bind_parameter
            | column_identifier >> !char_("(")
            | function_call
        );

    // Operator precedence climbing
    auto const bo_lhs_p1 =                       expr_left_def;
    auto const bo_lhs_p2 = binary_operation_p1 | expr_left_def;
    auto const bo_lhs_p3 = binary_operation_p2 | expr_left_def;
    auto const bo_lhs_p4 = binary_operation_p3 | expr_left_def;
    auto const bo_lhs_p5 = binary_operation_p4 | expr_left_def;
    auto const bo_lhs_p6 = binary_operation_p5 | expr_left_def;
    auto const bo_lhs_p7 = binary_operation_p6 | expr_left_def;
    auto const bo_lhs_p8 = binary_operation_p7 | expr_left_def;

    auto const bo_rhs_p1 =                       bo_lhs_p1;
    auto const bo_rhs_p2 = binary_operation_p2 | bo_lhs_p2;
    auto const bo_rhs_p3 = binary_operation_p3 | bo_lhs_p3;
    auto const bo_rhs_p4 = binary_operation_p4 | bo_lhs_p4;
    auto const bo_rhs_p5 = binary_operation_p5 | bo_lhs_p5;
    auto const bo_rhs_p6 = binary_operation_p6 | bo_lhs_p6;
    auto const bo_rhs_p7 = binary_operation_p7 | bo_lhs_p7;
    auto const bo_rhs_p8 = binary_operation_p8 | bo_lhs_p8;

    auto const binary_operation_p1_def =
        (bo_lhs_p1 >> binary_operator_p1 >> bo_rhs_p1);

    auto const binary_operation_p2_def =
        (bo_lhs_p2 >> binary_operator_p2 >> bo_rhs_p2) | binary_operation_p1;

    auto const binary_operation_p3_def =
        (bo_lhs_p3 >> binary_operator_p3 >> bo_rhs_p3) | binary_operation_p2;

    auto const binary_operation_p4_def =
        (bo_lhs_p4 >> binary_operator_p4 >> bo_rhs_p4) | binary_operation_p3;

    auto const binary_operation_p5_def =
        (bo_lhs_p5 >> binary_operator_p5 >> bo_rhs_p5) | binary_operation_p4;

    auto const binary_operation_p6_def =
        (bo_lhs_p6 >> binary_operator_p6 >> bo_rhs_p6) | binary_operation_p5;

    auto const binary_operation_p7_def =
        (bo_lhs_p7 >> binary_operator_p7 >> bo_rhs_p7) | binary_operation_p6;

    auto const binary_operation_p8_def =
        (bo_lhs_p8 >> binary_operator_p8 >> bo_rhs_p8) | binary_operation_p7;

    // Instead of implementing precedence climbing we could also
    // establish operator precendences in a post processing step by
    // implementing the shunting yardalgorithm by Edsger W. Dijkstra.
    // In this case the binary operation parser definition would look
    // as follows:
    /*
    auto const binary_operation_p8_def =
                    expr_left_def >> (
                              binary_operator_p1
                            | binary_operator_p2
                            | binary_operator_p3
                            | binary_operator_p4
                            | binary_operator_p5
                            | binary_operator_p6
                            | binary_operator_p7
                            | binary_operator_p8
                    ) >> expr;
    */

    auto const binary_operation = binary_operation_p8;

    // https://www.sqlite.org/syntax/expr.html
    //
    auto const expr_def =
        (
              binary_operation_p8
            | expr_left_def
        );

    auto const expr_list_def = expr % ',';

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( bind_parameter )
    BOOST_SPIRIT_DEFINE( schema_column_identifier )
    BOOST_SPIRIT_DEFINE( table_column_identifier )
    BOOST_SPIRIT_DEFINE( simple_column_identifier )
    BOOST_SPIRIT_DEFINE( column_identifier )
    BOOST_SPIRIT_DEFINE( function_params_expr_list )
    BOOST_SPIRIT_DEFINE( function_params_none )
    BOOST_SPIRIT_DEFINE( function_params_row )
    BOOST_SPIRIT_DEFINE( function_params )
    BOOST_SPIRIT_DEFINE( function_call )
    BOOST_SPIRIT_DEFINE( binary_operation_p1 )
    BOOST_SPIRIT_DEFINE( binary_operation_p2 )
    BOOST_SPIRIT_DEFINE( binary_operation_p3 )
    BOOST_SPIRIT_DEFINE( binary_operation_p4 )
    BOOST_SPIRIT_DEFINE( binary_operation_p5 )
    BOOST_SPIRIT_DEFINE( binary_operation_p6 )
    BOOST_SPIRIT_DEFINE( binary_operation_p7 )
    BOOST_SPIRIT_DEFINE( binary_operation_p8 )
    BOOST_SPIRIT_DEFINE( expr )
    BOOST_SPIRIT_DEFINE( expr_list )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct bind_parameter_class                       : annotate_on_success {};

    struct schema_column_identifier_class             : annotate_on_success {};
    struct table_column_identifier_class              : annotate_on_success {};
    struct simple_column_identifier_class             : annotate_on_success {};
    struct column_identifier_class                    : annotate_on_success {};

    struct function_params_expr_list_class            : annotate_on_success {};
    struct function_params_none_class                 : annotate_on_success {};
    struct function_params_row_class                  : annotate_on_success {};
    struct function_params_class                      : annotate_on_success {};
    struct function_call_class                        : annotate_on_success {};

    struct binary_operation_p1_class                  : annotate_on_success {};
    struct binary_operation_p2_class                  : annotate_on_success {};
    struct binary_operation_p3_class                  : annotate_on_success {};
    struct binary_operation_p4_class                  : annotate_on_success {};
    struct binary_operation_p5_class                  : annotate_on_success {};
    struct binary_operation_p6_class                  : annotate_on_success {};
    struct binary_operation_p7_class                  : annotate_on_success {};
    struct binary_operation_p8_class                  : annotate_on_success {};

    struct expr_class                                 : annotate_on_success {};
    struct expr_list_class                            : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_EXPR_HPP
