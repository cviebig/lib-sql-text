#ifndef SQL_TEXT_SUPPORT_VARIANT_TEST_VISITORS_HPP
#define SQL_TEXT_SUPPORT_VARIANT_TEST_VISITORS_HPP

namespace sql { namespace text { namespace support {

    // This static visitor returns true if the given variant
    // instantiation is of type T. Else false.
    template<typename T>
    struct variant_type_check_visitor
            : public boost::static_visitor<bool> {
        bool operator()(T &rc) const {
            return true;
        }

        template<typename F>
        bool operator()(F &rc) const {
            return false;
        }
    };

}}}

#endif //SQL_TEXT_SUPPORT_VARIANT_TEST_VISITORS_HPP
