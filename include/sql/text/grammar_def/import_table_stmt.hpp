#ifndef SQL_TEXT_GRAMMAR_DEF_IMPORT_TABLE_STMT_HPP
#define SQL_TEXT_GRAMMAR_DEF_IMPORT_TABLE_STMT_HPP

#include "sql/text/grammar/import_table_stmt.hpp"

#include "sql/text/grammar_def/literal_value.hpp"
#include "sql/text/grammar_def/table_or_subquery.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

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

    auto const fchar_def =
        alnum | char_('.') | char_('_') | char_('-') | char_('/') | char_('\\')
        | char_(':');

    auto const import_table_source_csv_def =
        lit("CSV") >> lit("FILE") >> lexeme[+fchar]
        >> lit("DELIMITED") >> lit("BY") >> string_literal;

    auto const import_table_source_def = import_table_source_csv;

    auto const import_table_stmt_def =
        lit("IMPORT") >> lit("TABLE")
        >> table_identifier
        >> lit("FROM")
        >> import_table_source;

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( fchar )
    BOOST_SPIRIT_DEFINE( import_table_source_csv )
    BOOST_SPIRIT_DEFINE( import_table_source )
    BOOST_SPIRIT_DEFINE( import_table_stmt )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct fchar_class {};
    struct import_table_source_csv_class              : annotate_on_success {};
    struct import_table_source_class                  : annotate_on_success {};
    struct import_table_stmt_class                    : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_IMPORT_TABLE_STMT_HPP
