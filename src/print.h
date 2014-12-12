#pragma once

#include <iostream>
#include "msg.h"

namespace print
{
    Msg& m(Msg& msg)
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
        Msg msg(str);
        m(msg, args...);
        out << msg.str();
    }
}
