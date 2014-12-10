#include <stdexcept>

class cstr
{public:
    template<unsigned int N>
    constexpr cstr(const char (&str)[N]) :length_(N-1), pstr_(str) {} 

    constexpr unsigned int length() const { return length_; }
    constexpr char operator[](int i) const { 
        return i < length_?  pstr_[i]: throw std::out_of_range(""); }

private:
    const unsigned int length_;
    const char* const pstr_;
};


constexpr unsigned int char_count(cstr str, char c, unsigned int i=0) 
{
    return 
        i == str.length()? 
            0: 
            str[i] == c? 
                1 + char_count(str, c, i+1):
                0 + char_count(str, c, i+1);
}

constexpr unsigned int percent_count(cstr str, unsigned int i=0) 
{
    return char_count(str, '%', i);
}

constexpr unsigned long long nth_bit(unsigned char n)
{
    return n? 1 << (n - 1): 0;
}

constexpr unsigned long long arg_seq(
    cstr str, char escape='%', char id='%', unsigned int count_arg = 0, unsigned int i=0)
{
    /****
     *   Hello %s, I'm %s. I have 23.0%% fat rate.
     *         ^-      ^-             ^-
     */
    return i >= str.length()?
            0:
            str[i] != escape?
                arg_seq(str, escape, id, count_arg, i+1): // non % case, advance to next i.
                i + 1 >= str.length()?
                    arg_seq(str, escape, id, count_arg, i+1): // only one % at tail. ignore it
                    str[i + 1] == escape?
                        arg_seq(str, escape, id, count_arg, i+2): // jump over %%
                        id == escape? (
                            nth_bit(1+count_arg) | arg_seq(str, escape, id, count_arg + 1, i+2)
                        ):(
                            str[i+1] == id?
                                nth_bit(1+count_arg) | arg_seq(str, escape, id, count_arg + 1, i+2):
                                arg_seq(str, escape, id, count_arg + 1, i+1) // bypass unknown arg id
                        );
}

constexpr unsigned long long 
str_arg_seq(cstr str, char escape='%')
{
    return arg_seq(str, escape, 's');
}

constexpr unsigned long long 
int_arg_seq(cstr str, char escape='%')
{
    return arg_seq(str, escape, 'd');
}

constexpr unsigned long long 
float_arg_seq(cstr str, char escape='%')
{
    return 0; //arg_seq(str, escape, 'd');
}
