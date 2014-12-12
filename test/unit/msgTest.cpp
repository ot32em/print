#include "bandit_base.h"
#include "msg.h"

go_bandit([]()
{
    describe("Msg add and str", []()
    {
        PtrT<Msg> pMsgWithString;
        PtrT<Msg> pMsgWithInt;
        PtrT<Msg> pMsgWithFloat;
        before_each([&]() {
            pMsgWithString.reset(new Msg(cstr("Hello %s.")));
            pMsgWithInt.reset(new Msg(cstr("Lucky %d.")));
            pMsgWithFloat.reset(new Msg(cstr("%f %% juice.")));
        });

        describe("Msg with string", [&]() {
            it("adds world", [&](){
                pMsgWithString->add("world");
                AssertThat(pMsgWithString->str(), Equals("Hello world."));
            });
            it("adds John", [&](){
                pMsgWithString->add("John");
                AssertThat(pMsgWithString->str(), Equals("Hello John."));
            });
        });

        describe("Add integer to MsgWithInt", [&]() {
            it("adds 7", [&]() {
                pMsgWithInt->add(7);
                AssertThat(pMsgWithInt->str(), Equals("Lucky 7."));
            });
            
            it("adds 5566", [&]() {
                pMsgWithInt->add(5566);
                AssertThat(pMsgWithInt->str(), Equals("Lucky 5566."));
            });
        });

        describe("Add float number to MsgWithFloat", [&]() {
            it("adds 75.5", [&]() {
                pMsgWithFloat->add(75.5);
                AssertThat(pMsgWithInt->str(), Equals("75.5 % juice."));
            });
            
            it("adds 100.0", [&]() {
                pMsgWithFloat->add(100.0);
                AssertThat(pMsgWithInt->str(), Equals("100 % juice."));
            });
        });


    });

    describe("args counts", [&]() {
        it("runs no args", [&]() {
            AssertThat(Msg(cstr("%% %%")).count_args(), Equals(0));
            AssertThat(Msg(cstr("abc abc %% %%")).count_args(), Equals(0));
            AssertThat(Msg(cstr("dce de%%")).count_args(), Equals(0));
            AssertThat(Msg(cstr("asflkjsafklw")).count_args(), Equals(0));
        });

        it("runs 1 arg", [&]() {
            AssertThat(Msg(cstr("%% %d")).count_args(), Equals(1));
            AssertThat(Msg(cstr("abc %f abc %% %%")).count_args(), Equals(1));
            AssertThat(Msg(cstr("dce%d de%%")).count_args(), Equals(1));
            AssertThat(Msg(cstr("asfl%skjsafklw")).count_args(), Equals(1));
        });

        it("runs 5 args", [&]() {
            AssertThat(Msg(cstr("%s %d %d %f %s")).count_args(), Equals(5));
            AssertThat(Msg(cstr("%sf%s%d%fa%sf")).count_args(), Equals(5));
            AssertThat(Msg(cstr("%f%s%d%%s%f%%s%d")).count_args(), Equals(5));
            AssertThat(Msg(cstr("Hello %s %f is %d and %d and %f")).count_args(), Equals(5));
        });
    });
    
    describe("str args counts", [&]() {
        it("runs no args", [&]() {
            AssertThat(Msg(cstr("%% %%")).count_args(Msg::ArgType::Str), Equals(0));
        });
        it("runs 0 arg - 2", [&](){
            AssertThat(Msg(cstr("abc abc %f %%")).count_args(Msg::ArgType::Str), Equals(0));
        });
        it("runs 0 arg - 3", [&](){
            AssertThat(Msg(cstr("dce de%d")).count_args(Msg::ArgType::Str), Equals(0));
        });
        it("runs 0 arg - 4", [&](){
            AssertThat(Msg(cstr("as%flkjs%daklw")).count_args(Msg::ArgType::Str), Equals(0));
        });

        it("runs 1 arg - 1", [&]() {
            AssertThat(Msg(cstr("%s %d")).count_args(Msg::ArgType::Str), Equals(1));
        });
        it("runs 1 arg - 2", [&](){
            AssertThat(Msg(cstr("abc %s abc %% %%")).count_args(Msg::ArgType::Str), Equals(1));
        });
        it("runs 1 arg - 3", [&](){
            AssertThat(Msg(cstr("dce%d de%s")).count_args(Msg::ArgType::Str), Equals(1));
        });
        it("runs 1 arg - 4", [&](){
            AssertThat(Msg(cstr("asfl%skjsafklw")).count_args(Msg::ArgType::Str), Equals(1));
        });

        it("runs 5 args", [&]() {
            AssertThat(Msg(cstr("%s %s %s %s %s")).count_args(Msg::ArgType::Str), Equals(5));
        });
        it("runs 5 args - 2", [&]() {
            AssertThat(Msg(cstr("%sf%s%d%sa%sf%s")).count_args(Msg::ArgType::Str), Equals(5));
        });
        it("runs 5 args - 3", [&]() {
            AssertThat(Msg(cstr("%%s%s%s%%d%%s%f%s%d%s%%%s")).count_args(Msg::ArgType::Str), Equals(5));
        });
        it("runs 5 args - 4", [&]() {
            AssertThat(Msg(cstr("Hello %s %s is %s and %s and %s")).count_args(Msg::ArgType::Str), Equals(5));
        });
    });
});
