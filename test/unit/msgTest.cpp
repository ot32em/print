#include "bandit_base.h"
#include "Msg.h"

go_bandit([]() {
    describe("Msg", []() {
        Msg msg(cstr("Hello %s, This is %dth day to drink %f%% %s juice."));

        it("add vals", [&](){
            msg.add("world");
            msg.add(7);
            msg.add(99.9);
            msg.add("orange");
            AssertThat(msg.str(), 
                Equals("Hello world, This is 7th day to drink 99.9% orange juice."));
        });
    });
});
