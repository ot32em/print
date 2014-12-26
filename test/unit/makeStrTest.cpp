#include "bandit_base.h"
#include "make_str.h"

go_bandit([]() {
    describe("make_str", [&]() {
        it("combines all const char*", [&]() {
            std::string str = make_str("Hello", " world.", " This", " is", " OT's", " speaking.");
            AssertThat(str, Equals(std::string("Hello world. This is OT's speaking.")));
        });

        it("makes with no args", [&]() {
            std::string str = make_str();
            AssertThat(str, Equals(std::string()));
        });

        it("combines args with different types", [&]() {
            std::string to = " world.";
            std::string from = " OT's"; 
            int time = 7;
            std::string str = make_str("Hello", to, " This", " is", from, " ", time, "th", " speaking.");
            AssertThat(str, Equals(std::string("Hello world. This is OT's 7th speaking.")));
        });
    });
});
