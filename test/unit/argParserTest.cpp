#include "bandit_base.h"
#include "arg_parser.h"

go_bandit([]()
{
    describe("ArgParser", []()
    {
        ArgParser ap(cstr("Hello %s, This is %dth day to drink %f%% %s juice."));
        //                        01234 6789 1234 6789 1234 6789 1234 6789 1234 6789
        it("args_count", [&](){
            AssertThat(ap.count_args(), Equals(4));
        });
        it("deals 0th arg", [&]() {
            AssertThat(ap[0].type, Equals('s'));
            AssertThat(ap[0].pos, Equals(6));
        });
        it("deals 1th arg", [&](){
            AssertThat(ap[1].type, Equals('d'));
            AssertThat(ap[1].pos, Equals(18));
        });
        it("deals 2th arg", [&](){
            AssertThat(ap[2].type, Equals('f'));
            AssertThat(ap[2].pos, Equals(36));
        });
        it("deals 3th arg", [&](){
            AssertThat(ap[3].type, Equals('s'));
            AssertThat(ap[3].pos, Equals(41));
        });
    });
});
