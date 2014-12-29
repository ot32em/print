#pragma once

#include <iostream>
#include "Msg.h"
#include "cargseq.h"

namespace print
{
    inline Msg& m(Msg& msg)
    {
        return msg;
    }

    template<typename T, typename ...ArgsT>
    Msg& m(Msg& msg, const T& v, const ArgsT... args)
    {
        msg.add(v);
        return m(msg, args...);
    }

    template<unsigned N, typename ...ArgsT>
    void f(std::ostream& out, const char (&str)[N], const ArgsT... args)
    {
        static_assert(sizeof...(ArgsT) == count_bit1(arg_seq(cstr("ss"))), "");
        Msg msg(str);
        m(msg, args...);
        out << msg.str();
    }
}
