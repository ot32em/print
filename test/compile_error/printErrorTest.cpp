#include <sstream>
#include <iostream>
#include "print.h"

using s_t = std::ostringstream;
int main()
{
    s_t out;
    print::f(out, "Hello %s.");
    std::cout << "hi" << std::endl;
    return 0;

}
