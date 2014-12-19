#include "bandit_base.h"
#include "cargseq.h"


#define TEST_STR "%s %f %s %d %d %f %% %%%% %d%% %s%% %d%d%d %f%f"
//                s     s                        s                3
//                         d  d             d         d d d       6
//                   f           f                           f f  4
//                                  %  % %    %    %              5
//
//                0  1  2  3  4  5  6  7 8  9 0  1 2  3 4 5  6 7
go_bandit([]()
{
    describe("arg_seq", [&]() {
        it("any args", [&]() {
            static_assert(any_arg_seq(cstr(TEST_STR), '*') == -1LLU >> (63 - 17), 
                "should be 0000 0000 0000 0011  1111 1111 1111 1111");
        });
        it("str args", [&]() {
            static_assert(any_arg_seq(cstr(TEST_STR), 's') ==  bit_at(0) || bit_at(2) || bit_at(11), 
                "should be 0000 0000 0000 0000  0000 1000 0000 0101");
        });
        it("int args", [&]() {
            static_assert(any_arg_seq(cstr(TEST_STR), 'd') ==  bit_at(3) || bit_at(4) || bit_at(9) || bit_at(13) || bit_at(14) || bit_at(15),
                "should be 0000 0000 0000 0000  1110 0010 0001 1000");
        });
        it("float args", [&]() {
            static_assert(any_arg_seq(cstr(TEST_STR), 'f') == bit_at(1) || bit_at(5) || bit_at(16) || bit_at(17),
                "should be 0000 0000 0000 0011  0000 0000 0010 0010");
        });
        it("% args", [&]() {
            static_assert(any_arg_seq(cstr(TEST_STR), '%') == bit_at(6) || bit_at(7) || bit_at(8) || bit_at(10) || bit_at(12),
                "should be 0000 0000 0000 0000  0001 0101 1100 0000");
        });
    });
});
