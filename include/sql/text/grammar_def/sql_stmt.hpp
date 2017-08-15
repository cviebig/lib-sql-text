#ifndef SQL_TEXT_GRAMMAR_DEF_SQL_STMT_HPP
#define SQL_TEXT_GRAMMAR_DEF_SQL_STMT_HPP

#include "sql/text/grammar/sql_stmt.hpp"

#include "sql/text/grammar_def/create_table_stmt.hpp"
#include "sql/text/grammar_def/import_table_stmt.hpp"
#include "sql/text/grammar_def/select_stmt.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const explain_clause_def =
        (
            omit[lit("EXPLAIN")] >> attr(true)
            >> matches[lit("QUERY") >> lit("PLAN")]
        )
        | (attr(false) >> attr(false));

    // https://www.sqlite.org/syntax/sql-stmt.html
    //
    auto const sql_stmt_def =
        explain_clause
        >> (
                 select_stmt
               | create_table_stmt
               | import_table_stmt
	         );

    // https://www.sqlite.org/syntax/sql-stmt-list.html
    //
    auto const sql_stmt_list_def = sql_stmt % ';';
    // Alternative *(sql_stmt) with sql_stmt requiring a trailing semi colon

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( explain_clause )
    BOOST_SPIRIT_DEFINE( sql_stmt )
    BOOST_SPIRIT_DEFINE( sql_stmt_list )

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct explain_clause_class                       : annotate_on_success {};
    struct sql_stmt_class                             : annotate_on_success {};
    struct sql_stmt_list_class                        : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_SQL_STMT_HPP
