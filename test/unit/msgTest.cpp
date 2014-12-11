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
        it("runs no args", [&]() {
            AssertThat(Msg("%% %%").count_format_count(), Equals(0));
            AssertThat(Msg("abc abc %% %%").count_format_count(), Equals(0));
            AssertThat(Msg("dce de%%").count_format_count(), Equals(0));
            AssertThat(Msg("asflkjsafklw").count_format_count(), Equals(0));
        });

        it("runs 1 arg", [&]() {
            AssertThat(Msg("%% %d").count_format_count(), Equals(1));
            AssertThat(Msg("abc %f abc %% %%").count_format_count(), Equals(1));
            AssertThat(Msg("dce%d de%%").count_format_count(), Equals(1));
            AssertThat(Msg("asfl%skjsafklw").count_format_count(), Equals(1));
        });

        it("runs 5 args", [&]() {
            AssertThat(Msg("%s %d %d %f %s").count_format_count(), Equals(5));
            AssertThat(Msg("%sf%s%d%fa%sf").count_format_count(), Equals(5));
            AssertThat(Msg("%f%s%d%%s%f%%s%d").count_format_count(), Equals(5));
            AssertThat(Msg("Hello %s %f is %d and %d and %f").count_format_count(), Equals(5));
        });
    });
});
