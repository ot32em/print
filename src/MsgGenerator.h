#pragma once

#include "cstr.h"
#include "ArgType.h"
#include "ArgExtractor.h"
#include "ArgValue.h"

class MsgGenerator
{public:
    MsgGenerator(
        cstr s,
        const std::vector<ArgToken>& arg_tokens,
        const ArgValue& av)
        : src_msg_(s.str()), arg_tokens_(arg_tokens), ae_(av)
    {}

    std::string generate()
    {
        std::size_t submsg_begin = 0;
        for(const ArgToken& arg: arg_tokens_)
        {
            dst_msg_ += src_msg_.substr(submsg_begin, arg.pos - submsg_begin);
            dst_msg_ += ae_.extract_next(arg.type);
            submsg_begin = arg.pos + 2;
        }
        dst_msg_ += src_msg_.substr(submsg_begin, src_msg_.size() - submsg_begin);
        return dst_msg_;
    }

private:
    const std::vector<ArgToken> arg_tokens_;
    const std::string src_msg_;
    ArgExtractor ae_;
    std::string dst_msg_;
};
