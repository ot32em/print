#include "../bandit_base.h"
#include "cstr.h"

go_bandit([]()
{
    describe("count bits", []()
    {
        it(" counts 1 bits", []()
        {
            static_assert(bit1_count(8) == 1, "");
        });

        it("counts 0 bits", []()
        {
            static_assert(bit0_count(8) == 63, "");
        });
    });
});
