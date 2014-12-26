#include "bandit_base.h"
#include "make_str.h"

go_bandit([]() {
    it("make_str", [&]() {
        std::string str = make_str("Hello", " world.", " This", " is", " OT's", " speaking.");
        AssertThat(str, Equals(std::string("Hello world. This is OT's speaking.")));
    });

    it("make_str no args", [&]() {
        std::string str = make_str();
        AssertThat(str, Equals(std::string()));
    });

    it("make_str with different types", [&]() {
        std::string to = " world.";
        std::string from = " OT's"; 
        int time = 7;
        std::string str = make_str("Hello", to, " This", " is", from, " ", time, "th", " speaking.");
        AssertThat(str, Equals(std::string("Hello world. This is OT's 7th speaking.")));
    });
});
