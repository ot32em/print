#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"

class Msg
{public:
    enum class ArgType {Any, Str};
    template<unsigned int N>
    Msg(const char (&msg)[N])
        :msg_(msg),
         str_args_(count_bit1(arg_seq(cstr(msg))))
    {
        for(std::size_t i = 0; i < str_args_.size(); i++)
        {
            if(bit_at(i) & str_arg_seq(msg))
            {
                str_args_[i] = std::make_pair(true, "");
            }
        }
    }

    void add(const char* str)
    {
    };

    std::string str() const
    {
        return msg_;
    }

    std::size_t count_format_count(ArgType t = ArgType::Any) const 
    { 
        switch(t)
        {
            case ArgType::Str:
                return  0;
                //std::count_if(str_args_.begin(), str_args_.end(), [](const std::pair<bool, std::string>& v) { return v.first; });
            default:
                return str_args_.size(); 
        }
    } private:
    std::string msg_;

    std::vector<std::pair<bool, std::string>> str_args_;
};
