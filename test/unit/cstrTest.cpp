#include "bandit/bandit.h"
#include "cstr.h"

using namespace bandit;

go_bandit([](){
    describe("Compile Time String", [](){
        it("counts msg length", [&]()
        {
            static_assert(
                cstr("Hello world.").length() == 12, 
                "msg's length should be 8.");
        });
        it("counts symbol count", [&]()
        {
            static_assert(
                char_count(cstr("Hello %"), '%') == 1 ,
                "msg should have one #.");
        });

        describe("args seqeunce", [&](){
            it("has no args", [&]()
            {
                static_assert(arg_seq(cstr("Hello world."), '%') == 0,
                "should return (0000) to represent no args");
            });
            it("has 1 str arg", [&]()
            {
                static_assert(arg_seq(cstr("Hello %s."), '%') == 1,
                "should return (0001) to represent 1 arg");
            });
            it("has 2 str arg", [&]()
            {
                static_assert(arg_seq(cstr("%s %s."), '%') == 2,
                "should return (0011) to represent 2 args");
            });
            it("has 3 str args", [&]()
            {
                static_assert(arg_seq(cstr("Hey %s %s, I'm %s."), '%') == 4,
                "should return (0111) to represent 3 args");
            });
            it("has 4 str args", [&]()
            {
                static_assert(arg_seq(cstr("Hey %s %s, I'm %s %s."), '%') == 8,
                "should return (1111) to represent 4 args");
            });
        });
    });
});

