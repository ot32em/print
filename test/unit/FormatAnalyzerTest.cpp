#include "bandit/bandit.h"
#include "FormatAnalyzer.h"

using namespace bandit;

go_bandit([](){
    describe("FormatAnalyzer"), [](){
        it("counts how many args in msg format", []()
        {
            describe("1-arg format message", []()
            {
                it("should counts 1", [&]()
                {
                    FormatAnalyzer fa("Hello %.");
                    static_assert(fa.args_count() == 1);
                }
            });
        });
    });
});

