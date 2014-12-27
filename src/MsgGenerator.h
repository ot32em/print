#pragma once

#include "cstr.h"
#include "ArgType.h"
#include "ArgValue.h"
#include "ArgExtractor.h"

class MsgGenerator
{public:
    MsgGenerator(
        cstr s,
        const std::vector<ArgToken>& arg_tokens,
        const ArgValue& av)
        : src_msg_(s.str()), 
		arg_tokens_(arg_tokens), 
		av_(av)
    {}

    std::string generate()
    {
		ArgExtractor ae(av_);
		std::string dst_msg;

        std::size_t submsg_begin = 0;
        for(const ArgToken& arg: arg_tokens_)
        {
            dst_msg += src_msg_.substr(submsg_begin, arg.pos - submsg_begin);
            dst_msg += ae.extract_next(arg.symbol);
            submsg_begin = arg.pos + 2;
        }
        dst_msg += src_msg_.substr(submsg_begin, src_msg_.size() - submsg_begin);
        return dst_msg;
    }

private:
    const std::string src_msg_;
    const std::vector<ArgToken> arg_tokens_;
	const ArgValue& av_;
};
