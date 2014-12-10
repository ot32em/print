#include "bandit_base.h"
#include "cbit.h"

go_bandit([]()
{
    describe("nth_bit", []()
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
    describe("bit1_count", []()
    {
        it("in 1 bit case", []()
        {
            static_assert(bit1_count(8) == 1, "");
        });
    });

    describe("bit0_count", []()
    {
        it("in 1 bit case", []()
        {
            static_assert(bit0_count(8) == 63, "");
        });
    });
});
