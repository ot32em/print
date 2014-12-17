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
                AssertThat(pMsgWithFloat->str(), Equals("75.5 % juice."));
            });
            
            it("adds 100.0", [&]() {
                pMsgWithFloat->add(100.0);
                AssertThat(pMsgWithFloat->str(), Equals("100.0 % juice."));
            });
        });


    });

    describe("counts_args", [&]() {
        Msg msg(cstr("%%s%s%s%%d%%s%f%s%d%s%%%s%f%%f%f%d%%d%d%%d%%%d"));
        //             %  s s %  %  f s d s % s f %  f d %  d %  % d

        it("counts str", [&]() {
            AssertThat(msg.count_args(Msg::ArgType::Str), Equals(5));
        });

        it("counts int", [&]() {
            AssertThat(msg.count_args(Msg::ArgType::Int), Equals(4));
        });

        it("counts float", [&]() {
            AssertThat(msg.count_args(Msg::ArgType::Float), Equals(3));
        });
    });
});
