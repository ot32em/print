#include "bandit_base.h"
#include "cargseq.h"

go_bandit([]() {
    describe("pos_of_nth_arg", []()
    {
        it("null case", []() {
            static_assert(pos_of_nth_arg(cstr(""), 0) == -1, "");

        });
        it("4 args simple case", []() {
            static_assert(pos_of_nth_arg(cstr("%f%f%f%f"), 0) == 0, "");
            static_assert(pos_of_nth_arg(cstr("%f%f%f%f"), 3) == 6, "");
            static_assert(pos_of_nth_arg(cstr("%f%f%f%f"), 4) == std::size_t(-1), "");
        });
        it("4 args with %% case", []() {
            static_assert(pos_of_nth_arg(cstr(" %s %% %d %f"), 0) == 1, "");
            static_assert(pos_of_nth_arg(cstr(" %s %% %d %f"), 1) == 4, "");
            static_assert(pos_of_nth_arg(cstr(" %s %% %d %f"), 2) == 7, "");
            static_assert(pos_of_nth_arg(cstr(" %s %% %d %f"), 3) == 10, "");
        });
    });

    describe("arg_type_at_bit", [&]() {
        #define SEQ1 bit_at(0,1,2)
        #define SEQ2 bit_at(0,1,2,3,4,5)
        #define SEQ3 bit_at(0,1,2,3,4,5,6,7,8)

        it("test bit0", [&]() {
            static_assert('1' == arg_type_at_bit(0, SEQ1, '1', SEQ2, '2', SEQ3, '3'),
                "all have bit0, but SEQ1 is tested first.");
        });
        it("test bit3", [&]() {
            static_assert('2' == arg_type_at_bit(3, SEQ1, '1', SEQ2, '2', SEQ3, '3'),
                "SEQ2 and SEQ3 both have bit3, but SEQ2 is tested first.");
        });
        it("test bit6", [&]() {
            static_assert('3' == arg_type_at_bit(6, SEQ1, '1', SEQ2, '2', SEQ3, '3'),
                "only SEQ3 has bit8.");
        });
        it("test bit9", [&]() {
            static_assert('?' == arg_type_at_bit(9, SEQ1, '1', SEQ2, '2', SEQ3, '3'),
                "no one has bit9, returns ?");
        });

    });
});
