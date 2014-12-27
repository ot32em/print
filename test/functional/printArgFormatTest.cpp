#include "bandit_base.h"
#include "print.h"
#include <sstream>

go_bandit([]() {
    describe("integer format", []() {
        it("", [&]() {
            std::ostringstream out;
            print::f(out, "%d", 1);
            AssertThat(out.str(), Equals("1"));
        });
    });
});
