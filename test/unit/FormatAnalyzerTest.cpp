#include "bandit/bandit.h"
#include "FormatAnalyzer.h"

using namespace bandit;

go_bandit([](){
    describe("Compile Time String", [](){
        it("counts msg length", [&]()
        {
            static_assert(
                std::integral_constant<
                    unsigned int,
                    cstr("Hello world.").length()
                >::value == 12, 
                "msg's length should be 8.");
        });
        it("counts symbol count", [&]()
        {
            static_assert(
                std::integral_constant<
                    unsigned int,
                    char_count(cstr("Hello %"), '%')
                >::value == 1 ,
                "msg should haveone #.");
        });
    });
});

