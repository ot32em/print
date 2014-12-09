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