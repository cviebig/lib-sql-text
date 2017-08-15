#ifndef SQL_TEXT_GRAMMAR_DEF_COMMON_HPP
#define SQL_TEXT_GRAMMAR_DEF_COMMON_HPP

#include "sql/text/grammar/common.hpp"

#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::attr;
    using boost::spirit::x3::lit;
    using boost::spirit::x3::omit;

    using boost::spirit::x3::annotate_on_success;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    auto const direction_type_def =
        (
           omit[lit("ASC")] >> attr(::sql::ast::direction_type::asc)
         | omit[lit("DESC")] >> attr(::sql::ast::direction_type::desc)
         | attr(::sql::ast::direction_type::omitted)
        );

    ///////////////////////////////////////////////////////////////////////////
    // Definition
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_DEFINE( direction_type );

    ///////////////////////////////////////////////////////////////////////////
    // Annotation and Error handling
    ///////////////////////////////////////////////////////////////////////////

    struct direction_type_class                       : annotate_on_success {};

}}

#endif //SQL_TEXT_GRAMMAR_DEF_COMMON_HPP
