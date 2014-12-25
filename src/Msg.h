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

void validate_arg_type(const ArgToken& arg, char c, const char* err_msg="")
{
    if(arg.type != c)
    {
        throw AddingWrongTypeArg(err_msg);
    }
}

class Msg
{public:
    Msg(cstr msg):
        msg_(msg),
        ap_(msg),
        added_args_(0),
        av_(ap_.count_args(symbol::Str()),
            ap_.count_args(symbol::Int()),
            ap_.count_args(symbol::Float()))
    {
    }

    void add(const char* str)
    {
        std::size_t arg_i = ap_.next_nonescape_arg_i(added_args_++);
        validate_arg_type(ap_[arg_i], symbol::Str(), "Adding a string");
        av_.add(str);
    };

    void add(int v)
    {
        std::size_t arg_i = ap_.next_nonescape_arg_i(added_args_++);
        validate_arg_type(ap_[arg_i], symbol::Int(), "Adding a integer");
        av_.add(v);
    }

    void add(double v)
    {
        std::size_t arg_i = ap_.next_nonescape_arg_i(added_args_++);
        validate_arg_type(ap_[arg_i], symbol::Float(), "Adding a floating number");
        av_.add(v);
    }

    std::string str() const
    {
        if(added_args_ == 0) { return msg_.str(); }
        MsgGenerator mg(msg_, ap_.arg_tokens(), av_);
        return mg.generate();
    }

private:
    cstr msg_;
    ArgParser ap_;
    std::size_t added_args_;
    ArgValue av_;
};

