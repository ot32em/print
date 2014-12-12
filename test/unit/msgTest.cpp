#include "bandit_base.h"
#include "msg.h"

go_bandit([]()
{
    describe("Msg with `Hello %s.`", []()
    {
        PtrT<Msg> pMsg;
        before_each([&]() {
            pMsg.reset(new Msg(cstr("Hello %s.")));
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
            AssertThat(Msg(cstr("%% %%")).count_format(), Equals(0));
            AssertThat(Msg(cstr("abc abc %% %%")).count_format(), Equals(0));
            AssertThat(Msg(cstr("dce de%%")).count_format(), Equals(0));
            AssertThat(Msg(cstr("asflkjsafklw")).count_format(), Equals(0));
        });

        it("runs 1 arg", [&]() {
            AssertThat(Msg(cstr("%% %d")).count_format(), Equals(1));
            AssertThat(Msg(cstr("abc %f abc %% %%")).count_format(), Equals(1));
            AssertThat(Msg(cstr("dce%d de%%")).count_format(), Equals(1));
            AssertThat(Msg(cstr("asfl%skjsafklw")).count_format(), Equals(1));
        });

        it("runs 5 args", [&]() {
            AssertThat(Msg(cstr("%s %d %d %f %s")).count_format(), Equals(5));
            AssertThat(Msg(cstr("%sf%s%d%fa%sf")).count_format(), Equals(5));
            AssertThat(Msg(cstr("%f%s%d%%s%f%%s%d")).count_format(), Equals(5));
            AssertThat(Msg(cstr("Hello %s %f is %d and %d and %f")).count_format(), Equals(5));
        });
    });
    
    describe("str args counts", [&]() {
        it("runs no args", [&]() {
            AssertThat(Msg(cstr("%% %%")).count_format(Msg::ArgType::Str), Equals(0));
        });
        it("runs 0 arg - 2", [&](){
            AssertThat(Msg(cstr("abc abc %f %%")).count_format(Msg::ArgType::Str), Equals(0));
        });
        it("runs 0 arg - 3", [&](){
            AssertThat(Msg(cstr("dce de%d")).count_format(Msg::ArgType::Str), Equals(0));
        });
        it("runs 0 arg - 4", [&](){
            AssertThat(Msg(cstr("as%flkjs%daklw")).count_format(Msg::ArgType::Str), Equals(0));
        });

        it("runs 1 arg - 1", [&]() {
            AssertThat(Msg(cstr("%s %d")).count_format(Msg::ArgType::Str), Equals(1));
        });
        it("runs 1 arg - 2", [&](){
            AssertThat(Msg(cstr("abc %s abc %% %%")).count_format(Msg::ArgType::Str), Equals(1));
        });
        it("runs 1 arg - 3", [&](){
            AssertThat(Msg(cstr("dce%d de%s")).count_format(Msg::ArgType::Str), Equals(1));
        });
        it("runs 1 arg - 4", [&](){
            AssertThat(Msg(cstr("asfl%skjsafklw")).count_format(Msg::ArgType::Str), Equals(1));
        });

        it("runs 5 args", [&]() {
            AssertThat(Msg(cstr("%s %s %s %s %s")).count_format(Msg::ArgType::Str), Equals(5));
        });
        it("runs 5 args - 2", [&]() {
            AssertThat(Msg(cstr("%sf%s%d%sa%sf%s")).count_format(Msg::ArgType::Str), Equals(5));
        });
        it("runs 5 args - 3", [&]() {
            AssertThat(Msg(cstr("%%s%s%s%%d%%s%f%s%d%s%%%s")).count_format(Msg::ArgType::Str), Equals(5));
        });
        it("runs 5 args - 4", [&]() {
            AssertThat(Msg(cstr("Hello %s %s is %s and %s and %s")).count_format(Msg::ArgType::Str), Equals(5));
        });
    });
});
