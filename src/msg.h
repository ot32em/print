#include <tuple>
#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"
#include "arg_parser.h"

class Msg
{public:
    enum class ArgType {Any, Str};
    Msg(cstr msg): msg_(msg), ap_(msg), 
                   added_args_(0), added_strs_(0),
                   str_values_(ap_.count_args('s'))
    {
    } 

    void add(const char* str)
    {
        auto arg = ap_[added_args_++];
        if(arg.type != 's') {
            throw std::invalid_argument("should be str");
        }
        str_values_[added_strs_++] = str;
    };

    std::string str() const
    {
        if(str_values_.empty()) { return msg_.str(); }

        const std::string src(msg_.str());
        std::string result;
        std::size_t left_pos = 0;
        std::size_t merged_strs = 0;
        for(const auto& arg: ap_)
        {
            if(arg.type == 's')
            {
                std::size_t right_pos = arg.pos;
                result += src.substr(left_pos, right_pos - left_pos);
                result += str_values_[merged_strs++]; 
                left_pos = right_pos + 2;
            }
        }
        result += src.substr(left_pos, src.size() - left_pos);
        return result;
    }

    std::size_t count_args(ArgType t = ArgType::Any ) const 
    { 
        if(t == ArgType::Any) return ap_.count_args('%');
        return ap_.count_args('s');
    } 

private:
    cstr msg_;
    ArgParser ap_;
    std::size_t added_args_;
    std::vector<std::string> str_values_;
    std::size_t added_strs_;
};
