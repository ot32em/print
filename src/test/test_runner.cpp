#include "print.h"
#include <iostream>
#include <sstream>

void check_eq(const std::ostringstream& result_out, const char* expected, const char* msg)
{
    if(result_out.str() != expected)
    {
        std::cerr << "\nTest Failure. Case: " << msg << std::endl;
    }
    else
    {
        std::cerr << ".";
    }
}
int main()
{
    typedef std::ostringstream ostr;
    {
        {
            ostr out;
            print(out, "Hello world.");
            check_eq(out, "Hello world.", "plain_text");
        }
        /*
        {
            ostream out;
            print(out, "Hello %.", "world");
            check_eq(out, "Hello world.", "replace one string")
        }
        {
            ostream out;
            print(out, "Hello %. I am %.", "world", "OT");
            check_eq(out, "Hello world. I am OT.");
        }
        */
    }
    std::cout << "\ntest finishes.\n";
    return 0;
}
