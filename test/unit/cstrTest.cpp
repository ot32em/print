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
    });
    describe("compile time bit helper", []()
    {
        it("nth_bit", []()
        {
            static_assert(nth_bit(0) == 1, "0th should be 00000001"); 
            static_assert(nth_bit(1) == 2, "1th should be 00000010"); 
            static_assert(nth_bit(2) == 4, "2th should be 00000100"); 
            static_assert(nth_bit(3) == 8, "3th should be 00001000"); 
            static_assert(nth_bit(4) == 16, "4th should be 00010000"); 
            static_assert(nth_bit(5) == 32, "5th should be 00100000"); 
            static_assert(nth_bit(6) == 64, "6th should be 01000000"); 
            static_assert(nth_bit(7) == 128, "7th should be 10000000"); 
            static_assert(nth_bit(7) == 128, "7th should be 10000000"); 

            static_assert(nth_bit(8) == 256, "8th should be 10000000"); 
            static_assert(nth_bit(9) == 512, "9th should be 10000000"); 
            static_assert(nth_bit(10) == 1024, "10th should be 10000000"); 
            static_assert(nth_bit(11) == 2048, "11th should be 10000000"); 
            static_assert(nth_bit(12) == 4096, "12th should be 10000000"); 
            static_assert(nth_bit(13) == 8192, "13th should be 10000000"); 
            static_assert(nth_bit(14) == 16384, "14th should be 10000000"); 
            static_assert(nth_bit(15) == 32768 , "15th should be 10000000"); 
        });
    });
});
