#include "bandit_base.h"
#include "msg.h"

go_bandit([]()
{
    describe("Msg with `Hello %s.`", []()
    {
        PtrT<Msg> pMsg;
        before_each([&]() {
            pMsg.reset(new Msg("Hello %s"));
        });

        describe("Msg::str", [&]() {
            it("adds world", [&](){
                pMsg->add("world");
                AssertThat(pMsg->str(), Equals("Hello world."));
            });

            it("adds John", [&](){
                pMsg->add("John");
                AssertThat(pMsg->str(), Equals("Hello John."));
            });
        });

    });

    describe("args counts", [&]() {
        it("runs case 1", [&]() {
            AssertThat(Msg("%s %s").count_format_count(), Equals(2));
        });
    });
});
