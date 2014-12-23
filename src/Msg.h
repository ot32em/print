#include <tuple>
#include "cbit.h"
#include "cstr.h"
#include "cargseq.h"
#include "ArgParser.h"

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
        added_strs_(0),
        str_values_(ap_.count_args('s')),
        added_ints_(0),
        int_values_(ap_.count_args('d')),
        added_floats_(0),
        float_values_(ap_.count_args('f'))
    {
    }

    void add(const char* str)
    {
        auto arg = ap_.next_nonescape_arg(added_args_);
        validate_arg_type(arg, 's', "Adding a string");
        str_values_[added_strs_++] = str;
    };

    void add(int v)
    {
        auto arg = ap_.next_nonescape_arg(added_args_);
        validate_arg_type(arg, 'd', "Adding a integer");
        int_values_[added_ints_++] = (unsigned long long)v;
    }

    void add(double v)
    {
        auto arg = ap_.next_nonescape_arg(added_args_);
        validate_arg_type(arg, 'f', "Adding a floating number");
        float_values_[added_floats_++] = v;
    }

    std::string str() const
    {
        if(added_args_ == 0) { return msg_.str(); }

        const std::string src_msg(msg_.str());
        std::string dst_msg;
        std::size_t submsg_begin = 0;
        std::size_t merged_strs = 0;
        std::size_t merged_ints = 0;
        std::size_t merged_floats = 0;
        for(const auto& arg: ap_)
        {
            std::size_t submsg_end = arg.pos;
            dst_msg += src_msg.substr(submsg_begin, submsg_end - submsg_begin);
            if(arg.type == 's')
            {
                dst_msg += str_values_[merged_strs++];
            }
            else if(arg.type == 'd')
            {
                dst_msg += std::to_string(int_values_[merged_ints++]);
            }
            else if(arg.type == 'f')
            {
                char buf[32] = {};
                float val = float_values_[merged_floats++];
                sprintf(buf, "%.1f", val);
                dst_msg += buf;
            }
            else if(arg.type == '%')
            {
                dst_msg += "%";
            }
            submsg_begin = submsg_end + 2;
        }
        dst_msg += src_msg.substr(submsg_begin, src_msg.size() - submsg_begin);
        return dst_msg;
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

