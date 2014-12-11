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
            if(bit_at(i+1) & str_arg_seq(msg))
            {
                str_args_[i].first = true;
            }
        }
    }

    void add(const char* str)
    {
        auto& arg = str_args_[added_args_++];
        if(arg.first)
        {
            arg.second = str;
        }
    };

    std::string str() const
    {
        std::string result = msg_;
        for(const auto& arg: str_args_)
        {
            if(arg.first)
            {
               result += arg.second;
            }
        }
        return result;
    }

    std::size_t count_format(ArgType t = ArgType::Any) const 
    { 
        switch(t)
        {
            case ArgType::Str:
                return  std::count_if(str_args_.begin(), str_args_.end(), 
                    [](const std::pair<bool, std::string>& v) { return v.first; });
            default:
                return str_args_.size(); 
        }
    } 

private:
    std::string msg_;
    std::vector<std::pair<bool, std::string>> str_args_;
    std::size_t added_args_;
};
