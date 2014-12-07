#include <iostream>

void print(std::ostream& out)
{
    
}

template<typename T, typename ...ArgsT>
void print(std::ostream& out, const T& value, const ArgsT... args)
{
    out << value;
    print(out, args...);
}
