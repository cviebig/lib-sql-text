#ifndef SQL_TEXT_GRAMMAR_DEF_SQL_HPP
#define SQL_TEXT_GRAMMAR_DEF_SQL_HPP

#include "sql/text/grammar/sql.hpp"

#include "sql/text/grammar_def/sql_stmt.hpp"
#include "sql/text/parser/error_handler.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const sql_def = sql_stmt_list;

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( sql );

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct sql_class              : annotate_on_success, error_handler_base {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_SQL_HPP
