#include "bandit_base.h"
#include "ArgParser.h"

go_bandit([]()
{
    describe("ArgParser", []()
    {
        ArgParser ap(cstr("Hello %s, This is %dth day to drink %f%% %s juice."));
        //                        01234 6789 1234 6789 1234 6789 1234 6789 1234 6789
        it("args_count", [&](){
            AssertThat(ap.count_args(), Equals(5));
        });
        it("deals 0th arg", [&]() {
            AssertThat(ap[0].symbol, Equals(Symbol::Str()));
            AssertThat(ap[0].pos, Equals(6));
        });
        it("deals 1th arg", [&](){
            AssertThat(ap[1].symbol, Equals(Symbol::Int()));
            AssertThat(ap[1].pos, Equals(18));
        });
        it("deals 2th arg", [&](){
            AssertThat(ap[2].symbol, Equals(Symbol::Float()));
            AssertThat(ap[2].pos, Equals(36));
        });
        it("deals 3th arg", [&](){
            AssertThat(ap[3].symbol, Equals(Symbol::Esc()));
            AssertThat(ap[3].pos, Equals(38));
        });
        it("deals 4th arg", [&](){
            AssertThat(ap[4].symbol, Equals(Symbol::Str()));
            AssertThat(ap[4].pos, Equals(41));
        });
    });
});
