#pragma once

#include <stdexcept>

class cstr
{public:
    template<unsigned int N>
    constexpr cstr(const char (&str)[N]): length_(N-1), pstr_(str) {}

    constexpr unsigned int length() const { return length_; }
    constexpr unsigned int size() const { return length(); }

    constexpr char operator[](int i) const
    {
        return
            (i < length_)?
                pstr_[i]
            :
                throw std::out_of_range("of cstr");
    }
    constexpr const char* str() const
    {
        return pstr_? pstr_: throw std::invalid_argument("null cstr");
    }

private:
    const unsigned int length_;
    const char* const pstr_;
};


constexpr unsigned int count_char(cstr str, char c, unsigned int i=0)
{
    return
        (i == str.length())?
            0
        :(str[i] == c)?
            1 + count_char(str, c, i+1)
        :
            0 + count_char(str, c, i+1);
}
