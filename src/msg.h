#include <tuple>
#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"

class Msg
{public:
    enum class ArgType {Any, Str};
    template<unsigned int N>
    Msg(const char (&msg)[N])
        :msg_(msg),
         str_args_(count_bit1(arg_seq(cstr(msg)))),
         added_args_(0)
    {
        for(std::size_t i = 0; i < str_args_.size(); i++)
        {
            if(bit_at(i) & str_arg_seq(msg))
            {
                std::get<0>(str_args_[i]) = true;
                std::get<1>(str_args_[i]) = arg_pos_at(msg, i);
            }
        }
    }

    void add(const char* str)
    {
        auto& arg = str_args_[added_args_++];
        if(std::get<0>(arg))
        {
            std::get<2>(arg) = str;
        }
    };

    std::string str() const
    {
        if(str_args_.empty())
        {
            return msg_;
        }
        else
        {
            std::string result;
            result.reserve(msg_.size());
            std::size_t left_pos = 0;
            for(const auto& arg: str_args_)
            {
                if(std::get<0>(arg))
                {
                    std::size_t right_pos = std::get<1>(arg);
                    result += msg_.substr(left_pos, right_pos - left_pos);
                    result += std::get<2>(arg);
                    left_pos = right_pos + 2;
                }
            }
            result += msg_.substr(left_pos, msg_.size() - left_pos);
            return result;
        }
    }

    std::size_t count_format(ArgType t = ArgType::Any) const 
    { 
        switch(t)
        {
            case ArgType::Str:
                return  std::count_if(str_args_.begin(), str_args_.end(), 
                    [](const ArgInfo& v) { return std::get<0>(v); });
            default:
                return str_args_.size(); 
        }
    } 

private:
    using ArgInfo = std::tuple<bool, std::size_t, std::string>;
    std::string msg_;
    std::vector<ArgInfo> str_args_;
    std::size_t added_args_;
};
