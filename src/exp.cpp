#include <iostream>
#include "cstr.h"

int main(int argc, char** argv)
{
    std::cout << str_arg_seq(cstr("%s %% %d %d")) << std::endl;
    std::cout << str_arg_seq(cstr("%d %s %% %d")) << std::endl;
    std::cout << str_arg_seq(cstr("%% %d %s %d")) << std::endl;
    std::cout << str_arg_seq(cstr("%d %% %d %s")) << std::endl;
    return 0;
}
