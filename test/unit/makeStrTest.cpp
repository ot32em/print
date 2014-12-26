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
    describe("join_str", [&]() {
        it("jointer is string", [&]() {
            std::string str = join_str("YA", 1,2,3,4,5);
            AssertThat(str, Equals(std::string("1YA2YA3YA4YA5")));
        });
        it("jointer is a int", [&]() {
            std::string str = join_str(3345678, "Hi", "Yo", "Man", "Hey", "Hey");
            AssertThat(str, Equals(std::string("Hi3345678Yo3345678Man3345678Hey3345678Hey")));
        });

        it("jointee of different types", [&]() {
            std::string str = join_str(99, "Hi", 123, "Man", 456, "Hey");
            AssertThat(str, Equals(std::string("Hi9912399Man9945699Hey")));
        });
        
        it("Join nothing", [&]() {
            std::string str = join_str(111);
            AssertThat(str, Equals(std::string()));
        });
    });
});
