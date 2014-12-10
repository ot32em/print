#include "bandit_base.h"
#include "cstr.h"

go_bandit([]()
{
    describe("Compile Time String", []()
    {
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

    });
});
