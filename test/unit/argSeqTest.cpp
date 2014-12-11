#include "bandit_base.h"
#include "cargseq.h"

go_bandit([]()
{
    describe("any args seqeunce", [&](){
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

        static_assert(str_arg_seq(cstr("%d %% %s %d")) == 2, "");
        static_assert(str_arg_seq(cstr("%d %s %% %s")) == 2 + 4, "");
        static_assert(str_arg_seq(cstr("%% %s %s %d")) == 1 + 2, "");
        static_assert(str_arg_seq(cstr("%s %% %s %s")) == 1 + 2 + 4, "");
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

    describe("arg_pos_at", []()
    {
        it("null case", []()
        {
            static_assert(arg_pos_at(cstr(""), 0) == -1, "");

        });
        it("4 args simple case", []()
        {
            static_assert(arg_pos_at(cstr("%f%f%f%f"), 0) == 0, "");
            static_assert(arg_pos_at(cstr("%f%f%f%f"), 1) == 2, "");
            static_assert(arg_pos_at(cstr("%f%f%f%f"), 3) == 6, "");
            static_assert(arg_pos_at(cstr("%f%f%f%f"), 4) == std::size_t(-1), "");
        });

        it("4 args with %% case", []()
        {
            static_assert(arg_pos_at(cstr(" %s %% %d %f"), 0) == 1, "");
            static_assert(arg_pos_at(cstr(" %s %% %d %f"), 1) == 7, "");
            static_assert(arg_pos_at(cstr(" %s %% %d %f"), 2) == 9, "");
            static_assert(arg_pos_at(cstr(" %s %% %d %f"), 3) == -1, "");
        });
    });
});
