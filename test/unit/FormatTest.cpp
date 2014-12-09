#include "../bandit_base.h"
#include "format.h"

go_bandit([](){
    describe("Format", [](){
        it("format msg by replace argument.", []()
        {
            Format f("Hello %s.");
            f.add("world");
            AssertThat(f.str(), Equals("Hello world."));
        });
    });
});
