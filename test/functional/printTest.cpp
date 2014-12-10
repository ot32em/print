#include "../bandit_base.h"
#include "print.h"
#include <sstream>

go_bandit([](){
    describe("print::f", [&]()
    {
        std::ostringstream out;
        before_each([&]()
        {
            out.str("");
            out.clear();
        });

        it("prints simple message.", [&]()
        {
            print::f(out, "Hello world.");
            AssertThat(out.str(), Equals("Hello world."));
        });

        it("prints message with c strings", [&]()
        {
            print::f(out, "My name is %s. My cat's name is %s.", "OT", "Nini");
            AssertThat(out.str(), Equals("My name is OT. My cat's name is Nini."));
        });

        it("prints message with numbers", [&]()
        {
            print::f(out, "%d + %d = %d", 5, 5, 10);
            AssertThat(out.str(), Equals("5 + 5 = 10"));
        });

        it("prints message with floating numbers", [&]()
        {
            print::f(out, "The pi is %f. The half is %f.", 3.14, 0.5);
            AssertThat(out.str(), Equals("The pi is 3.14. The half is 0.5."));
        });

        describe("with mixed arguments.", [&]()
        {
            before_each([&]()
            {
                out.str("");
                out.clear();
            });

            it("prints weather reports.", [&]()
            {
                print::f(out, "%s! Today is %d/%d. Current degree is %f C.", "Good morning", 12, 8, 24.5);
                AssertThat(out.str(), Equals("Good morning! Today is 12/8. Current degree is 24.5 C."));
            });

            it("prints bills", [&]()
            {
                print::f(out, "I have %d %s. It cost me %d dollars.", 3, "apples", 75);
                AssertThat(out.str(), Equals("I have 3 apples. It cost me 75 dollars."));
            });
        });

        describe("with escape arguments %%", [&]()
        {
            before_each([&]()
            {
                out.str("");
                out.clear();
            });

            it("prints memory usage info", [&]()
            {
                print::f(out, "Memery Usage: %f%%.", 20.8);
                AssertThat(out.str(), Equals("Memory Usage: 20.8%."));
            });

            it("prints drink name.", [&]()
            {
                print::f(out, "%f%% %s juice.", 100.0, "orange");
                AssertThat(out.str(), Equals("100.0% orange juice."));
            });
        });
    });
});
