#include "bandit/bandit.h"
#include "print.h"
#include <sstream>

using namespace bandit;

go_bandit([](){
    describe("print test", [&](){
        std::ostringstream* pout;
        before_each([&](){
            pout = new std::ostringstream();
        });
        
        it("prints plain text and non args text", [&](){
            print(*pout, "Hello world.");
            
            AssertThat(pout->str(), Equals("Hello world."));
        });
    });
});
        

