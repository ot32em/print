#pragma once

#include "cstr.h"
#include "ArgType.h"
#include "ArgValueExtractor.h"
#include "ArgValue.h"

class MsgGenerator
{public:
    MsgGenerator(
        cstr s, const std::vector<ArgToken>& arg_tokens, const ArgValue& av)
        :
        src_msg_(s.str()), arg_tokens_(arg_tokens), av_(av) {}

    std::string generate() const
    {
        if(arg_tokens_.empty()) { return src_msg_; }

        std::string dst_msg;
        ArgValueExtractor ae(av_);
        dst_msg += head_substr();
        dst_msg += ae.extract_next(head_arg().symbol);
        for(std::size_t i = 1; i != arg_tokens_.size(); i++)
        {
            dst_msg += substr_between_args(prev_arg(i), curr_arg(i));
            dst_msg += ae.extract_next(curr_arg(i).symbol);
        }
        dst_msg += last_substr();
        return dst_msg;
    }

private:
    const ArgToken& head_arg() const { return arg_tokens_.front(); }
    const ArgToken& prev_arg(std::size_t i) const { return arg_tokens_[i-1]; }
    const ArgToken& curr_arg(std::size_t i) const { return arg_tokens_[i]; }
    const ArgToken& last_arg() const { return arg_tokens_.back(); }

    std::string substr_between_args(const ArgToken& lhs_arg, const ArgToken& rhs_arg) const
    {
        auto msg_begin = lhs_arg.pos + 2;
        auto msg_len = rhs_arg.pos - msg_begin;
        return src_msg_.substr(msg_begin, msg_len);
    }

    std::string head_substr() const
    {
        return src_msg_.substr(0, head_arg().pos);
    }

    std::string last_substr() const
    {
        auto msg_begin = last_arg().pos + 2;
        auto msg_len = src_msg_.length() - msg_begin;
        return src_msg_.substr(msg_begin, msg_len);
    }

private:
    const std::vector<ArgToken> arg_tokens_;
    const std::string src_msg_;
    const ArgValue& av_;
};
