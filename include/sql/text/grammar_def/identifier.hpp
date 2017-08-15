#ifndef SQL_TEXT_GRAMMAR_DEF_IDENTIFIER_HPP
#define SQL_TEXT_GRAMMAR_DEF_IDENTIFIER_HPP

#include "sql/text/grammar/identifier.hpp"

#include "sql/text/grammar_def/reserved_words.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lexeme;
    using boost::spirit::x3::lit;

    using boost::spirit::x3::ascii::alpha;
    using boost::spirit::x3::ascii::alnum;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const ialnum_def = alnum | (char('_') >> attr('_'));

    auto const identifier_def =
        (
                (lexeme[alpha >> *ialnum] - reserved_word)
                >>  attr(ast::quot::NONE)
            |   lit("\"") >> lexeme[+ialnum] >> lit("\"")
                >>  attr(ast::quot::DOUBLE)
            |   lit("[") >> lexeme[+ialnum] >> lit("]")
                >>  attr(ast::quot::SQUARED)
            |   lit("`") >> lexeme[+ialnum] >> lit("`")
                >>  attr(ast::quot::BACKTICK)
        );

    auto const identifier_list_def = identifier % ",";


    auto const simple_table_identifier_def = identifier;

    auto const schema_table_identifier_def = identifier >> '.' >> identifier;

    auto const table_identifier_def =
        (
              schema_table_identifier
            | simple_table_identifier
        );

    auto const aliased_table_identifier_def =
        table_identifier
        >>  -(-lit("AS") >> identifier);

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( ialnum )
    BOOST_SPIRIT_DEFINE( identifier )
    BOOST_SPIRIT_DEFINE( identifier_list )
    BOOST_SPIRIT_DEFINE( simple_table_identifier )
    BOOST_SPIRIT_DEFINE( schema_table_identifier )
    BOOST_SPIRIT_DEFINE( table_identifier )
    BOOST_SPIRIT_DEFINE( aliased_table_identifier )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct ialnum_class {};
    struct identifier_class                           : annotate_on_success {};
    struct identifier_list_class                      : annotate_on_success {};

    struct simple_table_identifier_class              : annotate_on_success {};
    struct schema_table_identifier_class              : annotate_on_success {};
    struct aliased_table_identifier_class             : annotate_on_success {};
    struct table_identifier_class                     : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_IDENTIFIER_HPP
