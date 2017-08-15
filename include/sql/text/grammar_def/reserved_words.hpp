#ifndef SQL_TEXT_GRAMMAR_DEF_RESERVED_WORDS_HPP
#define SQL_TEXT_GRAMMAR_DEF_RESERVED_WORDS_HPP

#include <boost/spirit/home/x3.hpp>

namespace sql { namespace text {

    using boost::spirit::x3::lit;

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    ///////////////////////////////////////////////////////////////////////////

    // https://sqlite.org/lang_keywords.html
    //
    auto const reserved_word =
        (lit("ABORT") | lit("ACTION") | lit("ADD") | lit("AFTER")
         | lit("ALL") | lit("ALTER") | lit("ANALYZE") | lit("AND")
         | lit("AS") | lit("ASC") | lit("ATTACH")
         | lit("AUTOINCREMENT") | lit("BEFORE") | lit("BEGIN")
         | lit("BETWEEN") | lit("BY") | lit("CASCADE")
         | lit("CASE") | lit("CAST") | lit("CHECK")
         | lit("COLLATE") | lit("COLUMN") | lit("COMMIT")
         | lit("CONFLICT") | lit("CONSTRAINT") | lit("CREATE")
         | lit("CROSS") | lit("CURRENT_DATE") | lit("CURRENT_TIME")
         | lit("CURRENT_TIMESTAMP") | lit("DATABASE")
         | lit("DEFAULT") | lit("DEFERRABLE") | lit("DEFERRED")
         | lit("DELETE") | lit("DESC") | lit("DETACH")
         | lit("DISTINCT") | lit("DROP") | lit("EACH")
         | lit("ELSE") | lit("END") | lit("ESCAPE") | lit("EXCEPT")
         | lit("EXCLUSIVE") | lit("EXISTS") | lit("EXPLAIN")
         | lit("FAIL") | lit("FOR") | lit("FOREIGN") | lit("FROM")
         | lit("FULL") | lit("GLOB") | lit("GROUP") | lit("HAVING")
         | lit("IF") | lit("IGNORE") | lit("IMMEDIATE") | lit("IN")
         | lit("INDEX") | lit("INDEXED") | lit("INITIALLY")
         | lit("INNER") | lit("INSERT") | lit("INSTEAD")
         | lit("INTERSECT") | lit("INTO") | lit("IS")
         | lit("ISNULL") | lit("JOIN") | lit("KEY") | lit("LEFT")
         | lit("LIKE") | lit("LIMIT") | lit("MATCH")
         | lit("NATURAL") | lit("NO") | lit("NOT") | lit("NOTNULL")
         | lit("NULL") | lit("OF") | lit("OFFSET") | lit("ON")
         | lit("OR") | lit("ORDER") | lit("OUTER") | lit("PLAN")
         | lit("PRAGMA") | lit("PRIMARY") | lit("QUERY")
         | lit("RAISE") | lit("RECURSIVE") | lit("REFERENCES")
         | lit("REGEXP") | lit("REINDEX") | lit("RELEASE")
         | lit("RENAME") | lit("REPLACE") | lit("RESTRICT")
         | lit("RIGHT") | lit("ROLLBACK") | lit("ROW")
         | lit("SAVEPOINT") | lit("SELECT") | lit("SET")
         | lit("TABLE") | lit("TEMP") | lit("TEMPORARY")
         | lit("THEN") | lit("TO") | lit("TRANSACTION")
         | lit("TRIGGER") | lit("UNION") | lit("UNIQUE")
         | lit("UPDATE") | lit("USING") | lit("VACUUM")
         | lit("VALUES") | lit("VIEW") | lit("VIRTUAL")
         | lit("WHEN") | lit("WHERE") | lit("WITH")
         | lit("WITHOUT"));

}}

#endif //SQL_TEXT_GRAMMAR_DEF_RESERVED_WORDS_HPP
