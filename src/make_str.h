template <typename... ArgsT>
std::string make_str(ArgsT... args)
{
    return "";
    /*
    std::ostringstream oss;
    make_stream(oss, args...);
    return oss.str();
    */
}


void make_stream(std::ostream& out) { }

template<typename T, typename... ArgsT>
void make_stream(std::ostream& out, const T& val, ArgsT... args)
{
    out << val;
    make_stream(out, args...);
}
