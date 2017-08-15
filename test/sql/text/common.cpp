#include "sql/text/grammar_def/common.hpp"
#include "sql/text/parser_def/parse.hpp"
#include "test.hpp"

namespace sql { namespace text {

    TEST_CASE( "Direction omitted", "[common]" ) {
        auto e = parse(direction_type, "");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Direction: ASC", "[common]" ) {
        auto e = parse(direction_type, "ASC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

    TEST_CASE( "Direction: DESC", "[common]" ) {
        auto e = parse(direction_type, "DESC");

        CHECK( e.success );
        CHECK( e.finished );
        CHECK( e.remainder == 0 );
    }

}}
