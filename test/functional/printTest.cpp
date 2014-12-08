#include "bandit/bandit.h"
#include "print.h"
#include <sstream>

using namespace bandit;

using StreamT = std::ostringstream;

go_bandit([](){
    describe("print function", [&]()
    {
        const char* hello_world = "Hello world.";
        it("should prints non-args format message.", [&]()
        {
            StreamT out;
            print(out, "Hello world.");
            AssertThat(out.str(), Equals(hello_world));
        });

        it("should prints 1-arg message with a string.", [&]()
        {
            StreamT out;
            print(out, "Hello %.");
            AssertThat(out.str(), Equals(hello_world));
        });
    });
});
        

