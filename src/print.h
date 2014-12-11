#pragma once

#include <iostream>

namespace print
{
    void f(std::ostream& out)
    {
        
    }

    template<typename T, typename ...ArgsT>
    void f(std::ostream& out, const T& value, const ArgsT... args)
    {
        out << value;
        f(out, args...);
    }
}
