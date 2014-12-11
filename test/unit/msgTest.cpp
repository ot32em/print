#include "bandit_base.h"
#include "msg.h"

go_bandit([]()
{
    describe("Msg with Hello", []()
    {
        PtrT<Msg> pMsg;
        before_each([&]() {
            pMsg.reset(new Msg("Hello %s"));
        });

        it("to world", [&](){
            pMsg->add("world");
            AssertThat(pMsg->str(), Equals("Hello world."));
        });

        it("to John", [&](){
            pMsg->add("John");
            AssertThat(pMsg->str(), Equals("Hello John."));
        });
    });
});
