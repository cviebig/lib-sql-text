#ifndef SQL_TEXT_GRAMMAR_IDENTIFIER_HPP
#define SQL_TEXT_GRAMMAR_IDENTIFIER_HPP

#include "sql/fusion/identifier.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct ialnum_class;
    struct identifier_class;
    struct identifier_list_class;

    struct simple_table_identifier_class;
    struct schema_table_identifier_class;
    struct table_identifier_class;
    struct aliased_table_identifier_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<ialnum_class, char>
    ialnum = "ialnum";

    const rule<identifier_class, ast::identifier>
    identifier = "identifier";

    const rule<identifier_list_class, ast::identifier_list>
    identifier_list = "identifier_list";


    const rule<simple_table_identifier_class, ast::simple_table_identifier>
    simple_table_identifier = "simple_table_identifier";

    const rule<schema_table_identifier_class, ast::schema_table_identifier>
    schema_table_identifier = "schema_table_identifier";

    const rule<table_identifier_class, ast::table_identifier>
    table_identifier = "table_identifier";

    const rule<aliased_table_identifier_class, ast::aliased_table_identifier>
    aliased_table_identifier = "aliased_table_identifier";

}}

#endif //SQL_TEXT_GRAMMAR_IDENTIFIER_HPP
