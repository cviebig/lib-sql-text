#ifndef SQL_TEXT_GRAMMAR_IMPORT_TABLE_STMT_HPP
#define SQL_TEXT_GRAMMAR_IMPORT_TABLE_STMT_HPP

#include "sql/fusion/import_table_stmt.hpp"

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::rule;

    ///////////////////////////////////////////////////////////////////////////
    // Rule IDs
    ///////////////////////////////////////////////////////////////////////////

    struct fchar_class;
    struct import_table_source_csv_class;
    struct import_table_source_class;
    struct import_table_stmt_class;

    ///////////////////////////////////////////////////////////////////////////
    // Rules
    ///////////////////////////////////////////////////////////////////////////

    const rule<fchar_class, char>
    fchar = "fchar";

    const rule<import_table_source_csv_class, ast::import_table_source_csv>
    import_table_source_csv = "import_table_source_csv";

    const rule<import_table_source_class, ast::import_table_source>
    import_table_source = "import_table_source";

    const rule<import_table_stmt_class, ast::import_table_stmt>
    import_table_stmt = "import_table_stmt";

}}

#endif //SQL_TEXT_GRAMMAR_IMPORT_TABLE_STMT_HPP
