#include <tuple>
#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"
#include "arg_parser.h"

class Msg
{public:
    enum class ArgType {Any, Str};
    Msg(cstr msg): msg_(msg), ap_(msg), 
                   added_args_(0), added_str_args_(0)
    {
        for(std::size_t i = 0; i != ap_.count_args(); i++) {
            if(ap_[i].type == 's') {
                str_args_.push_back(std::make_pair(i, ""));
            }
        }
    } 

    void add(const char* str)
    {
        auto arg = ap_[added_args_++];
        if(arg.type != 's') {
            throw std::invalid_argument("should be str");
        }
        str_args_[added_str_args_++].second = str;
    };

    std::string str() const
    {
        if(str_args_.empty()) { return msg_.str(); }

        std::string src(msg_.str());
        std::string result;
        std::size_t left_pos = 0;
        std::size_t merged_str_arg = 0;
        for(const auto& arg: ap_)
        {
            if(arg.type == 's')
            {
                std::size_t right_pos = arg.pos;
                result += src.substr(left_pos, right_pos - left_pos);
                result += str_args_[merged_str_arg++].second; 
                left_pos = right_pos + 2;
            }
        }
        result += src.substr(left_pos, src.size() - left_pos);
        return result;
    }

    std::size_t count_format(ArgType t = ArgType::Any ) const 
    { 
        if(t == ArgType::Any) return ap_.count_args('%');
        return ap_.count_args('s');
    } 

private:
    cstr msg_;
    std::size_t added_args_;
    std::size_t added_str_args_;
    ArgParser ap_;
    std::vector<std::pair<unsigned, std::string>> str_args_;
};
