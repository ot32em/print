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
});
