#pragma once

#include <tuple>
#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"
#include "ArgParser.h"
#include "ArgValue.h"
#include "MsgGenerator.h"

struct AddingWrongTypeArg : public std::invalid_argument
{
    AddingWrongTypeArg(const char* msg): std::invalid_argument(msg){}
};

void validate_arg_type(const ArgParser::ArgInfo& arg, char c, const char* err_msg="")
{
    if(arg.type != c)
    {
        throw AddingWrongTypeArg(err_msg);
    }
}

class Msg
{public:
    enum class ArgType {Any, Str, Int, Float};
    Msg(cstr msg):
        msg_(msg),
        ap_(msg),
        added_args_(0),
        av_(ap_.count_args('s'),
            ap_.count_args('d'),
            ap_.count_args('f'))
    {
    }

    void add(const char* str)
    {
        auto arg = ap_.next_nonescape_arg(added_args_);
        validate_arg_type(arg, 's', "Adding a string");
        av_.add(str);
    };

    void add(int v)
    {
        auto arg = ap_.next_nonescape_arg(added_args_);
        validate_arg_type(arg, 'd', "Adding a integer");
        av_.add(v);
    }

    void add(double v)
    {
        auto arg = ap_.next_nonescape_arg(added_args_);
        validate_arg_type(arg, 'f', "Adding a floating number");
        av_.add(v);
    }

    std::string str() const
    {
        if(added_args_ == 0) { return msg_.str(); }
        MsgGenerator mg(msg_, ap_.arg_info_list(), av_);
        return mg.generate();
    }

private:
    cstr msg_;
    ArgParser ap_;
    std::size_t added_args_;
    ArgValue av_;
};

