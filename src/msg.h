#include <tuple>
#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"
#include "arg_parser.h"

class Msg
{public:
    enum class ArgType {Any, Str, Int};
    Msg(cstr msg): msg_(msg), ap_(msg), 
                   added_args_(0), added_strs_(0), added_ints_(0),
                   str_values_(ap_.count_args('s')),
                   int_values_(ap_.count_args('d'))
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

    void add(int v)
    {
        if(ap_[added_args_++].type != 'd') {
            throw std::invalid_argument("should be integer.");
        }
        int_values_[added_ints_++] = (unsigned long long)v;
    }

    void add(double v)
    {
    }

    std::string str() const
    {
        if(added_args_ == 0) { return msg_.str(); }

        const std::string src(msg_.str());
        std::string result;
        std::size_t left_pos = 0;
        std::size_t merged_strs = 0;
        std::size_t merged_ints = 0;
        for(const auto& arg: ap_)
        {
            std::size_t right_pos = arg.pos;
            result += src.substr(left_pos, right_pos - left_pos);
            if(arg.type == 's') {
                result += str_values_[merged_strs++]; 
            } else if(arg.type == 'd') {
                result += std::to_string(int_values_[merged_ints++]); 
            }
            left_pos = right_pos + 2;
        }
        result += src.substr(left_pos, src.size() - left_pos);
        return result;
    }

    std::size_t count_args(ArgType t = ArgType::Any ) const 
    { 
        if(t == ArgType::Any) return ap_.count_args('%');
        else if(t == ArgType::Str) return ap_.count_args('s');
        return ap_.count_args('d');
    } 

private:
    cstr msg_;
    ArgParser ap_;
    std::size_t added_args_;
    std::vector<std::string> str_values_;
    std::size_t added_strs_;

    std::vector<unsigned long long> int_values_;
    std::size_t added_ints_;
};
