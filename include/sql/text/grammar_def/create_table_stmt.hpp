#ifndef SQL_TEXT_GRAMMAR_DEF_CREATE_TABLE_STMT_HPP
#define SQL_TEXT_GRAMMAR_DEF_CREATE_TABLE_STMT_HPP

#include "sql/text/grammar/create_table_stmt.hpp"

#include "sql/text/grammar_def/common.hpp"
#include "sql/text/grammar_def/identifier.hpp"
#include "sql/text/grammar_def/literal_value.hpp"
#include "sql/text/grammar_def/select_stmt.hpp"
#include "sql/text/grammar_def/table_or_subquery.hpp"

#include <boost/optional.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/support/unused.hpp>

namespace sql { namespace text {

    using ast::quot;

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::unused;

    using boost::spirit::x3::ascii::alpha;
    using boost::spirit::x3::ascii::char_;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    boost::optional<ast::numeric_literal> const empty_num;

    auto const type_def = +alpha;

    auto const type_name_bounded_def =
        type >> lit('(') >> numeric_literal >> lit(',') >> numeric_literal
        >> lit(')');

    auto const type_name_upper_bounded_def =
        type >> lit('(') >> attr(empty_num) >> numeric_literal >> lit(')');

    auto const type_name_unbounded_def =
        type >> attr(empty_num) >> attr(empty_num);

    // https://www.sqlite.org/syntax/type-name.html
    //
    auto const type_name_def =
        (
              type_name_bounded
            | type_name_upper_bounded
            | type_name_unbounded
        );

    // https://www.sqlite.org/syntax/column-def.html
    //
    auto const column_def_def = identifier >> type_name;

    auto const column_def_list_def = column_def % ',';

    // https://www.sqlite.org/syntax/indexed-column.html
    //
    auto const indexed_column_def = identifier >> direction_type;

    auto const indexed_column_list_def = indexed_column % ',';

    auto const table_constraint_primary_key_def =
        omit[lit("PRIMARY")] >> omit[lit("KEY")]
        >> omit[char_('(')] >> indexed_column_list >> omit[char_(')')]
        // conflict-clause
    ;

    auto const table_constraint_unique_def =
        omit[lit("UNIQUE")]
        >> omit[char_('(')] >> indexed_column_list >> omit[char_(')')]
        // conflict-clause
    ;

    auto const table_constraint_foreign_key_def =
        omit[lit("FOREIGN")] >> omit[lit("KEY")]
        >> omit[char_('(')] >> identifier_list >> omit[char_(')')]
        >> omit[lit("REFERENCES")] >> identifier
        >> omit[char_('(')] >> identifier_list >> omit[char_(')')]
        // further options
    ;

    auto const table_constraint_type_def =
        (
              table_constraint_primary_key
            | table_constraint_unique
            // table_constraint_check
            | table_constraint_foreign_key
        );

    // https://www.sqlite.org/syntax/table-constraint.html
    //
    auto const table_constraint_def =
        -(omit[lit("CONSTRAINT")] >> identifier)
        >> table_constraint_type;

    auto const table_constraint_list_def = table_constraint % ',';

    auto const create_table_stmt_columns_def =
           omit[char_('(')]
        >> column_def_list
        >> -(omit[char_(',')] >> table_constraint_list)
        >> omit[char_(')')]
        >> (omit[lit("WITHOUT") >> lit("ROWID")] >> attr(false) | attr(true));

    auto const create_table_stmt_select_def = lit("AS") >> select_stmt;

    auto const create_table_stmt_definition_def =
        (
              create_table_stmt_columns
            | create_table_stmt_select
        );

    auto const create_table_stmt_def =
           omit[lit("CREATE")]
        >> ((lit("TEMPORARY") | lit("TEMP")) >> attr(true) | attr(false))
        >> omit[lit("TABLE")]
        >> (lit("IF") >> lit("NOT") >> lit("EXISTS") >> attr(true) | attr(false))
        >> table_identifier
        >> create_table_stmt_definition;

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( type )
    BOOST_SPIRIT_DEFINE( type_name_bounded )
    BOOST_SPIRIT_DEFINE( type_name_upper_bounded )
    BOOST_SPIRIT_DEFINE( type_name_unbounded )
    BOOST_SPIRIT_DEFINE( type_name )
    BOOST_SPIRIT_DEFINE( column_def )
    BOOST_SPIRIT_DEFINE( column_def_list )
    BOOST_SPIRIT_DEFINE( indexed_column )
    BOOST_SPIRIT_DEFINE( indexed_column_list )
    BOOST_SPIRIT_DEFINE( table_constraint_primary_key )
    BOOST_SPIRIT_DEFINE( table_constraint_unique )
    BOOST_SPIRIT_DEFINE( table_constraint_foreign_key )
    BOOST_SPIRIT_DEFINE( table_constraint_type )
    BOOST_SPIRIT_DEFINE( table_constraint )
    BOOST_SPIRIT_DEFINE( table_constraint_list )
    BOOST_SPIRIT_DEFINE( create_table_stmt_columns )
    BOOST_SPIRIT_DEFINE( create_table_stmt_select )
    BOOST_SPIRIT_DEFINE( create_table_stmt_definition )
    BOOST_SPIRIT_DEFINE( create_table_stmt )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct type_class                                 : annotate_on_success {};
    struct type_name_bounded_class                    : annotate_on_success {};
    struct type_name_upper_bounded_class              : annotate_on_success {};
    struct type_name_unbounded_class                  : annotate_on_success {};
    struct type_name_class                            : annotate_on_success {};

    struct column_def_class                           : annotate_on_success {};
    struct column_def_list_class                      : annotate_on_success {};

    struct indexed_column_class                       : annotate_on_success {};
    struct indexed_column_list_class                  : annotate_on_success {};
    struct table_constraint_primary_key_class         : annotate_on_success {};
    struct table_constraint_unique_class              : annotate_on_success {};
    struct table_constraint_foreign_key_class         : annotate_on_success {};
    struct table_constraint_type_class                : annotate_on_success {};
    struct table_constraint_class                     : annotate_on_success {};
    struct table_constraint_list_class                : annotate_on_success {};

    struct create_table_stmt_columns_class            : annotate_on_success {};
    struct create_table_stmt_select_class             : annotate_on_success {};
    struct create_table_stmt_definition_class         : annotate_on_success {};

    struct create_table_stmt_class                    : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_CREATE_TABLE_STMT_HPP
