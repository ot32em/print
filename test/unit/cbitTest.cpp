#include "bandit_base.h"
#include "cbit.h"

go_bandit([]()
{
    describe("bit_at", []()
    {
        it("compare integers {0,1,2,4,8,...,32768}", []()
        {
            static_assert(bit_at(0) == 0,  "0th should be 00000000"); 
            static_assert(bit_at(1) == 1,  "1th should be 00000001"); 
            static_assert(bit_at(2) == 2,  "2th should be 00000010"); 
            static_assert(bit_at(3) == 4,  "3th should be 00000100"); 
            static_assert(bit_at(4) == 8,  "4th should be 00001000"); 
            static_assert(bit_at(5) == 16, "5th should be 00010000"); 
            static_assert(bit_at(6) == 32, "6th should be 00100000"); 
            static_assert(bit_at(7) == 64, "7th should be 01000000"); 
            static_assert(bit_at(8) == 128,"8th should be 10000000"); 

            static_assert(bit_at(9) == 256,     "9th should be 00000001 00000000"); 
            static_assert(bit_at(10) == 512,   "10th should be 00000010 00000000"); 
            static_assert(bit_at(11) == 1024,  "11th should be 00000100 00000000"); 
            static_assert(bit_at(12) == 2048,  "12th should be 00001000 00000000"); 
            static_assert(bit_at(13) == 4096,  "13th should be 00010000 00000000"); 
            static_assert(bit_at(14) == 8192,  "14th should be 00100000 00000000"); 
            static_assert(bit_at(15) == 16384, "15th should be 01000000 00000000"); 
            static_assert(bit_at(16) == 32768, "16th should be 10000000 00000000"); 
        });
    });

    describe("bit counters", [&](){
        const unsigned int n = 8;
        const unsigned int n2 = 8 + 1024;

        describe("count_bit1", [&]() {
            it("counts n", [&]() {
                static_assert(count_bit1(n) == 1, "");
            });
            it("counts n2", [&]() {
                static_assert(count_bit1(n2) == 2, "");
            });
        });

        describe("count_bit0", [&]() {
            it("counts n", [&]() {
                static_assert(count_bit0(n) == 63, "");
            });
            it("counts n2", [&]() {
                static_assert(count_bit0(n2) == 62, "");
            });
        });
    });
});
