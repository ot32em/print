#include <iostream>
#include <sstream>
#include <string>

void make_stream(std::ostream& out) { }

template<typename T, typename... ArgsT>
void make_stream(std::ostream& out, const T& val, ArgsT... args)
{
    out << val;
    make_stream(out, args...);
}

template <typename... ArgsT>
std::string make_str(ArgsT... args)
{
    std::ostringstream oss;
    make_stream(oss, args...);
    return oss.str();
}


template<typename JointerT>
void join_stream(std::ostream& out, const JointerT& jointer) { }

template<typename JointerT, typename T>
void join_stream(std::ostream& out, const JointerT& jointer, const T& final_val)
{
    out << final_val;
}

template<typename JointerT, typename T, typename... ArgsT>
void join_stream(std::ostream& out, const JointerT& jointer, const T& val, ArgsT... args)
{
    out << val << jointer;
    join_stream(out, jointer, args...);
}

template<typename JointerT, typename... ArgsT>
std::string join_str(const JointerT& jointer, ArgsT... args)
{
    std::ostringstream oss;
    join_stream(oss, jointer, args...);
    return oss.str();
}
