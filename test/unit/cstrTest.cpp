#include "bandit_base.h"
#include "cstr.h"

go_bandit([]()
{
    describe("cstr", []()
    {
        it("counts length", [&]()
        {
            static_assert(cstr("Hello world.").length() == 12, "");
            static_assert(cstr("Hello.").length() == 6, "");
            static_assert(cstr("YoHello.").length() == 8, "");
            static_assert(cstr("").length() == 0, "");
        });

        it("counts symbol count", [&]()
        {
            static_assert(char_count(cstr(""), '%') == 0 , "");
            static_assert(char_count(cstr("Hello"), '%') == 0 , "");
            static_assert(char_count(cstr("%"), '%') == 1 , "");
            static_assert(char_count(cstr("% % %"), '%') == 3 , "");
            static_assert(char_count(cstr("% % % Hello % % %"), '%') == 6 , "");
        });

    });
});
