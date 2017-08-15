SQL parsing library
===================

This package contains a Boost Spirit X3 [1] based parsing expression grammar
(PEG) [2] for a subset of the SQL dialect used in SQlite3 [3] and allows for
both use as a header-only library or as a shared library.

[1] http://ciere.com/cppnow15/x3_docs/index.html

[2] https://en.wikipedia.org/wiki/Parsing_expression_grammar

[3] https://www.sqlite.org/lang.html

.. highlight:: C++

Use
---

Declaration and definition of parsing expressions are split between header files
in `include/sql/text/grammar <include/sql/text/grammar>`_ and
`include/sql/text/grammar_def <include/sql/text/grammar_def>`_. Parser tooling
is provided in `include/sql/text/parser <include/sql/text/parser>`_ and
`include/sql/text/parser_def <include/sql/text/parser_def>`_ respectively.

Includes are suggested to refer to `include/sql/text/parser.hpp
<include/sql/text/parser.hpp>`_ for declarations (shared library use) and
`include/sql/text/parser_def.hpp <sql/text/parser_def.hpp>`_ for declarations
and implementations (header-only use).

Example::

   #include "sql/text/parser_def.hpp"

   ::sql::text::parse_result<::sql::ast::sql_stmt_list> result
       = ::sql::text::parse(::sql::text::parser, "SELECT A, B, C FROM Anything");

For the struct ``parse_result`` see `include/sql/text/parser/parse_result.hpp
<include/sql/text/parser/parse_result.hpp>`_.

Dependencies
------------

The parser generation depends on attributes defined in ``lib-sql`` [4].

[4] https://github.com/cviebig/lib-sql

Implementation
--------------

For it's grammar definitions X3 relies entirely on ordinary C++ syntax by
providing operator overloads to construct compound parsing expressions. By doing
so it's able to generate efficient parsers without relying on external tools
such as *flex*, *yacc* and *bison*.

Parsing rules are defined as instances of the template struct
``boost::spirit::x3::rule`` [5] and evaluated on input using the function
template ``boost::spirit::x3::phrase_parse`` [6].

The ``rule`` template takes two parameters. First an ``ID`` type which servies
as a unique tag and configures the parser to act on certain events like
``on_error`` or ``on_success``. Second an ``Attribute`` type which will hold the
result of the parsing step. ``Attribute`` types need to be adapted to Boost
Fusion. The adaption is needed to turn attribute types into heterogeneous
containers which are then filled during parsing.

After declaring a const variable of the rule instantiation we define the actual
parsing expression. These may be constructed from compound expressions of
terminal literals or, non-terminals such as other rules.

The expression is then bound to the ``rule`` by instantiating the macro
``BOOST_SPIRIT_DEFINE`` [5]. It is defining an overload of the free function
``parse_rule`` specialized to the rule and it's definition. Using macros
``BOOST_SPIRIT_DECLARE`` [5] and ``BOOST_SPIRIT_INSTANTIATE`` [5] it is also
possible to perform forward declaration and explicit template instantiation of
that function overload.

``rule`` instantiations are usually named according to the non-terminal in the
grammar. The ``ID`` type is taking the same name plus a ``_class`` suffix and
the actual parsing expression definition's name is suffixed with ``_def``. The
latter one is required by ``BOOST_SPIRIT_DEFINE`` macro.

Definitions and declarations are separated in this package as follows:

- Attribute structs in `lib-sql/include/sql/ast/
  <https://github.com/cviebig/lib-sql/blob/master/include/sql/ast/>`_
- Boost Fusion bindings in `lib-sql/include/sql/fusion/
  <https://github.com/cviebig/lib-sql/blob/master/include/sql/fusion/>`_
- Rule declaration in `lib-sql-text/include/sql/text/grammar/
  <include/sql/text/grammar/>`_
- Rule definition in `lib-sql-test/include/sql/text/grammar_def/
  <include/sql/text/grammar_def/>`_

An example
^^^^^^^^^^

The identifier grammar rule should be nice for serving as a brief example:

- `lib-sql/include/sql/ast/identifier.hpp
  <https://github.com/cviebig/lib-sql/blob/master/include/sql/ast/identifier.hpp>`_::

   // in namespace ::sql::ast
   enum class quot { NONE, SINGLE, DOUBLE, SQUARED, BACKTICK};
   struct identifier : boost::spirit::x3::position_tagged {
       std::string identifier;
       quot quotation;
   };

- `lib-sql/include/sql/fusion/identifier.hpp
  <https://github.com/cviebig/lib-sql/blob/master/include/sql/fusion/identifier.hpp>`_::

   BOOST_FUSION_ADAPT_STRUCT(sql::ast::identifier,
                            (std::string, identifier)
                            (sql::ast::quot, quotation))

- `lib-sql-text/include/sql/grammar/identifier.hpp
  <include/sql/text/grammar/identifier.hpp>`_::

   struct identifier_class;
   const rule<identifier_class, ast::identifier> identifier = "identifier";

- `lib-sql-text/include/sql/grammar_def/identifier.hpp
  <include/sql/text/grammar_def/identifier.hpp>`_::

   auto const identifier_def = (
        (lexeme[alpha >> *ialnum] - reserved_word) >> attr(ast::quot::NONE)
     |  lit("\"") >> lexeme[+ialnum] >> lit("\"")  >> attr(ast::quot::DOUBLE)
     /* ... */
   );
   BOOST_SPIRIT_DEFINE( identifier )
   struct identifier_class : boost::spirit::x3::annotate_on_success {};

[5] https://github.com/boostorg/spirit/tree/boost-1.64.0/include/boost/spirit/home/x3/nonterminal/rule.hpp

[6] https://github.com/boostorg/spirit/tree/boost-1.64.0/include/boost/spirit/home/x3/core/parse.hpp

External facing rules
---------------------

A rule that diverges in it's implementation from all the others is
``::sql::text::sql`` in `include/sql/grammar/sql.hpp
<include/sql/grammar/sql.hpp>`_. This is for two reasons. First it carries the
``on_error`` handler defined in `include/sql/text/parser/error_handler.hpp
<include/sql/text/parser/error_handler.hpp>`_ by inheritance in
`include/sql/text/grammar_def/sql.hpp <include/sql/text/grammar_def/sql.hpp>`_.
Second it is forward declared and explicitly template instantiated in
`include/sql/text/grammar/sql.hpp <include/sql/text/grammar/sql.hpp>`_ and
`src/sql/text/parser.cpp <src/sql/text/parser.cpp>`_ respectively. This is done
in order to satisfy the shared library use case.

Separate compilation units
--------------------------

Important to note is that all headers are self-contained. This fine as long one
want's to use the library either as a header-only library or as single
compilation unit shared library. If the grammar grows bigger it might be
favorable to trade the potential advantages of inlining with compilation speed
or parallelism. In order to compile each definition file in a separate
compilation unit just exchange includes of `grammar_def
<include/sql/text/grammar_def/>`_ headers with their counterparts in `grammar/
<include/sql/text/grammar/>`_ and add corresponding source files with
instantiations of ``BOOST_SPIRIT_INSTANTIATE``.

Known issues
------------

- Operator precedence for SQL binary expression operators is implemented using
  precedence climbing which might not be the most favorable implementation in
  regard to efficiency. See `include/sql/text/grammar_def/expr.hpp
  <include/sql/text/grammar_def/expr.hpp>`_
