#include "../bandit_base.h"
#include "msg.h"

go_bandit([]()
{
    describe("Msg", []()
    {
        it("formats one string arg.", []()
        {
            Msg m("Hello %s.");
            m.add("world");
            AssertThat(m.str(), Equals("Hello world."));
        });
    });
});
