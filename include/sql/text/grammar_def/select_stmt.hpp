#ifndef SQL_TEXT_GRAMMAR_DEF_SELECT_STMT_HPP
#define SQL_TEXT_GRAMMAR_DEF_SELECT_STMT_HPP

#include "sql/text/grammar/select_stmt.hpp"

#include "sql/text/grammar_def/common.hpp"
#include "sql/text/grammar_def/expr.hpp"
#include "sql/text/grammar_def/select_core.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    namespace x3 = boost::spirit::x3;

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::lexeme;
    using boost::spirit::x3::matches;
    using boost::spirit::x3::omit;

    using boost::spirit::x3::ascii::alnum;
    using boost::spirit::x3::ascii::alpha;
    using boost::spirit::x3::ascii::char_;
    using boost::spirit::x3::int_;
    using boost::spirit::x3::string;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    // https://www.sqlite.org/syntax/ordering-term.html
    //
    auto const ordering_term_def =
        expr >> direction_type;

    auto const ordering_term_list_def = ordering_term % ',';

    auto const orderby_clause_def =
        omit[lit("ORDER")] >> omit[lit("BY")] >> ordering_term_list >> attr(true);

    auto const limit_clause_def =
        omit[lit("LIMIT")] >> expr >> -(omit[lit(",")] | omit[lit("OFFSET")]) >> expr;

    // https://www.sqlite.org/syntax/factored-select-stmt.html
    //
    auto const select_stmt_def =
        select_core
        >> -(orderby_clause)
        >> -(limit_clause);

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( ordering_term )
    BOOST_SPIRIT_DEFINE( ordering_term_list )
    BOOST_SPIRIT_DEFINE( orderby_clause )
    BOOST_SPIRIT_DEFINE( limit_clause )
    BOOST_SPIRIT_DEFINE( select_stmt )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct ordering_term_class                        : annotate_on_success {};
    struct orderby_clause_class                       : annotate_on_success {};
    struct limit_clause_class                         : annotate_on_success {};
    struct select_stmt_class                          : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_SELECT_STMT_HPP
