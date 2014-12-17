#include <tuple>
#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"
#include "arg_parser.h"

class Msg
{public:
    enum class ArgType {Any, Str, Int, Float};
    Msg(cstr msg): msg_(msg), ap_(msg), 
                   added_args_(0), added_strs_(0), added_ints_(0), added_floats_(0),
                   str_values_(ap_.count_args('s')),
                   int_values_(ap_.count_args('d')),
                   float_values_(ap_.count_args('f'))
    {
    } 

    void add(const char* str)
    {
        auto arg = ap_[added_args_++];
        while(arg.type == '%')
        {
            if(added_args_ == ap_.count_args()) { throw std::invalid_argument("No more arg to escape when adding a string."); }
            arg = ap_[added_args_++];
        }
        if(arg.type != 's') { throw std::invalid_argument("Adding a string, but msg arg type does not match."); }
        str_values_[added_strs_++] = str;
    };

    void add(int v)
    {
        auto arg = ap_[added_args_++];
        while(arg.type == '%')
        {
            if(added_args_ == ap_.count_args()) { throw std::invalid_argument("No more arg to escape when adding a integer."); }
            arg = ap_[added_args_++];
        }
        if(arg.type != 'd') { throw std::invalid_argument("Adding a integer, but msg arg type does not match."); }
        int_values_[added_ints_++] = (unsigned long long)v;
    }

    void add(double v)
    {
        auto arg = ap_[added_args_++];
        while(arg.type == '%')
        {
            if(added_args_ == ap_.count_args()) { throw std::invalid_argument("No more arg to escape when adding a floating integer."); }
            arg = ap_[added_args_++];
        }
        if(arg.type != 'f') { throw std::invalid_argument("Adding a floating integer, but msg arg type does not match."); }
        float_values_[added_floats_++] = v;
    }

    std::string str() const
    {
        if(added_args_ == 0) { return msg_.str(); }

        const std::string src(msg_.str());
        std::string result;
        std::size_t left_pos = 0;
        std::size_t merged_strs = 0;
        std::size_t merged_ints = 0;
        std::size_t merged_floats = 0;
        for(const auto& arg: ap_)
        {
            std::size_t right_pos = arg.pos;
            result += src.substr(left_pos, right_pos - left_pos);
            if(arg.type == 's') {
                result += str_values_[merged_strs++]; 
            } else if(arg.type == 'd') {
                result += std::to_string(int_values_[merged_ints++]); 
            } else if(arg.type == 'f') {
                char buf[32] = {};
                float val = float_values_[merged_floats++];
                sprintf(buf, "%.1f", val);
                result += buf;
            }
            else if(arg.type == '%') {
                result += "%";
            }
            
            left_pos = right_pos + 2;
        }
        result += src.substr(left_pos, src.size() - left_pos);
        return result;
    }

    std::size_t count_args(ArgType t = ArgType::Any) const 
    { 
        if(t == ArgType::Str) { return ap_.count_args('s'); }
        if(t == ArgType::Int) { return ap_.count_args('d'); }
        if(t == ArgType::Float) { return ap_.count_args('f'); }
        if(t == ArgType::Any) { return ap_.count_args('%'); }
        throw std::invalid_argument("count_args meet unknown type");
    } 

private:
    cstr msg_;
    ArgParser ap_;
    std::size_t added_args_;
    std::vector<std::string> str_values_;
    std::size_t added_strs_;

    std::vector<unsigned long long> int_values_;
    std::size_t added_ints_;

    std::vector<double> float_values_;
    std::size_t added_floats_;
};
