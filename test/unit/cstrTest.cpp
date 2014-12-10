#include "bandit/bandit.h"
#include "cstr.h"

using namespace bandit;

go_bandit([](){
    describe("Compile Time String", [](){
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

        describe("args seqeunce", [&](){
            it("has no args", [&]()
            {
                static_assert(arg_seq(cstr("Hello world."), '%') == 0,
                "should return (0000) to represent no args");
            });
            it("has 1 str arg", [&]()
            {
                static_assert(arg_seq(cstr("Hello %s."), '%') == 1,
                "should return (0001) to represent 1 arg");
            });
            it("has 2 str arg", [&]()
            {
                static_assert(arg_seq(cstr("%s %s."), '%') == 2+1,
                "should return (0011) to represent 2 args");
            });
            it("has 3 str args", [&]()
            {
                static_assert(arg_seq(cstr("Hey %s %s, I'm %s."), '%') == 4+2+1,
                "should return (0111) to represent 3 args");
            });
            it("has 4 str args", [&]()
            {
                static_assert(arg_seq(cstr("Hey %s %s, I'm %s %s."), '%') == 8+4+2+1,
                "should return (1111) to represent 4 args");
            });
        });

        describe("str args sequence", []()
        {
            static_assert(str_arg_seq(cstr("%s %d %d %d")) == 1, "");
            static_assert(str_arg_seq(cstr("%d %s %d %d")) == 2, "");
            static_assert(str_arg_seq(cstr("%d %d %s %d")) == 4, "");
            static_assert(str_arg_seq(cstr("%d %d %d %s")) == 8, "");
            static_assert(str_arg_seq(cstr("%s %s %d %d")) == 1 + 2, "");
            static_assert(str_arg_seq(cstr("%s %d %s %d")) == 1 + 4, "");
            static_assert(str_arg_seq(cstr("%s %d %d %s")) == 1 + 8, "");
            static_assert(str_arg_seq(cstr("%d %s %s %d")) == 2 + 4, "");
            static_assert(str_arg_seq(cstr("%d %s %d %s")) == 2 + 8, "");
            static_assert(str_arg_seq(cstr("%s %s %s %d")) == 1 + 2 + 4, "");
            static_assert(str_arg_seq(cstr("%s %s %s %s")) == 1 + 2 + 4 + 8, "");

            static_assert(str_arg_seq(cstr("%d %% %s %d")) == 4, "");
            static_assert(str_arg_seq(cstr("%d %s %% %s")) == 2 + 8, "");
            static_assert(str_arg_seq(cstr("%% %s %s %d")) == 2 + 4, "");
            static_assert(str_arg_seq(cstr("%s %% %s %s")) == 1 + 4 + 8, "");
        });

        describe("int args sequence", []()
        {
            static_assert(int_arg_seq(cstr("%s %d %d %d")) == 2 + 4 + 8, "");
            static_assert(int_arg_seq(cstr("%d %s %d %d")) == 1 + 4 + 8, "");
            static_assert(int_arg_seq(cstr("%d %d %s %d")) == 1 + 2 + 8, "");
            static_assert(int_arg_seq(cstr("%d %d %d %s")) == 1 + 2 + 4, "");
            static_assert(int_arg_seq(cstr("%s %s %d %d")) == 4 + 8, "");
            static_assert(int_arg_seq(cstr("%s %d %s %d")) == 2 + 8, "");
            static_assert(int_arg_seq(cstr("%s %d %d %s")) == 2 + 4, "");
            static_assert(int_arg_seq(cstr("%d %s %s %d")) == 1 + 8, "");
            static_assert(int_arg_seq(cstr("%d %s %d %s")) == 1 + 4, "");
            static_assert(int_arg_seq(cstr("%s %s %s %d")) == 8, "");
            static_assert(int_arg_seq(cstr("%s %s %s %s")) == 0, "");
        });

        describe("float args sequence", []()
        {
            static_assert(float_arg_seq(cstr("%s %f %f %f")) == 2 + 4 + 8, "");
            static_assert(float_arg_seq(cstr("%f %s %f %f")) == 1 + 4 + 8, "");
            static_assert(float_arg_seq(cstr("%f %f %s %f")) == 1 + 2 + 8, "");
            static_assert(float_arg_seq(cstr("%f %f %f %s")) == 1 + 2 + 4, "");
            static_assert(float_arg_seq(cstr("%s %s %f %f")) == 4 + 8, "");
            static_assert(float_arg_seq(cstr("%s %f %s %f")) == 2 + 8, "");
            static_assert(float_arg_seq(cstr("%s %f %f %s")) == 2 + 4, "");
            static_assert(float_arg_seq(cstr("%f %s %s %f")) == 1 + 8, "");
            static_assert(float_arg_seq(cstr("%f %s %f %s")) == 1 + 4, "");
            static_assert(float_arg_seq(cstr("%s %s %s %f")) == 8, "");
            static_assert(float_arg_seq(cstr("%s %s %s %s")) == 0, "");
        });
    });
    describe("compile time bit helper", []()
    {
        it("nth_bit", []()
        {
            static_assert(nth_bit(0) == 0,  "0th should be 00000000"); 
            static_assert(nth_bit(1) == 1,  "1th should be 00000001"); 
            static_assert(nth_bit(2) == 2,  "2th should be 00000010"); 
            static_assert(nth_bit(3) == 4,  "3th should be 00000100"); 
            static_assert(nth_bit(4) == 8,  "4th should be 00001000"); 
            static_assert(nth_bit(5) == 16, "5th should be 00010000"); 
            static_assert(nth_bit(6) == 32, "6th should be 00100000"); 
            static_assert(nth_bit(7) == 64, "7th should be 01000000"); 
            static_assert(nth_bit(8) == 128,"8th should be 10000000"); 

            static_assert(nth_bit(9) == 256,     "9th should be 00000001 00000000"); 
            static_assert(nth_bit(10) == 512,   "10th should be 00000010 00000000"); 
            static_assert(nth_bit(11) == 1024,  "11th should be 00000100 00000000"); 
            static_assert(nth_bit(12) == 2048,  "12th should be 00001000 00000000"); 
            static_assert(nth_bit(13) == 4096,  "13th should be 00010000 00000000"); 
            static_assert(nth_bit(14) == 8192,  "14th should be 00100000 00000000"); 
            static_assert(nth_bit(15) == 16384, "15th should be 01000000 00000000"); 
            static_assert(nth_bit(16) == 32768, "16th should be 10000000 00000000"); 
        });
    });
});
