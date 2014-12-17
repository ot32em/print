#include <iostream>
#include "cstr.h"
#include "cargseq.h"

#define TEST_STR "%s %f %s %d %d %f %% %%%% %d%% %s%% %d%d%d %f%f"

int main(int argc, char** argv)
{
    std::cout << any_arg_seq("%% %% %% %% %%", '%', '*') << std::endl;
    std::cout << any_arg_seq(TEST_STR, '%', '*') << std::endl;
    std::cout << ( -1ULL >> (63-17) ) << std::endl;
    return 0;
}
