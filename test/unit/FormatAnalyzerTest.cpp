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
                    CStr("Hello world.").length()>::value == 12, 
                    "Its length should be 8.");
        });
        it("counts symbaol count", [&]()
        {
            static_assert(
                std::integral_constant<
                    unsigned int,
                    char_count(CStr("Hello %"), '%')
                    >::value == 1 , "msg has one #.");
        });
    });
});

