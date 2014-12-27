#include "bandit_base.h"
#include "print.h"
#include <sstream>

using s_t = std::ostringstream;

go_bandit([]() {
    describe("integer format", []() {
        it("decimal", [&]() {
            s_t out;
            print::f(out, "%d", 1);
            AssertThat(out.str(), Equals("1"));
        });

        it("decimal", [&]() {
            s_t out;
            print::f(out, "%i", 1);
            AssertThat(out.str(), Equals("1"));
        });

        it("lower heximal", [&]() {
            s_t out;
            print::f(out, "%h %h %h", 15, 10, 8);
            AssertThat(out.str(), Equals("f a 8"));
        });

        it("Upper heximal", [&]() {
            s_t out;
            print::f(out, "%H %H %H", 15, 10, 8);
            AssertThat(out.str(), Equals("F A 8"));
        });

        it("oct", [&]() {
            s_t out;
            print::f(out, "%o %o %o", 15, 10, 7);
            AssertThat(out.str(), Equals("17 12 7")); 
        });
    });
});
