#pragma once

#include "ArgValue.h"
#include "make_str.h"

class ArgValueExtractor
{public:
    ArgValueExtractor(const ArgValue& av)
        :av_(av),
        extracted_strs_(0),
        extracted_ints_(0),
        extracted_floats_(0)
    {}

    std::string extract_next(char arg_symbol)
    {
        switch(arg_symbol)
        {
            case Symbol::Str(): 
                return av_.str_as_str(extracted_strs_++);
            case Symbol::Int(): 
                return av_.int_as_str(extracted_ints_++);
            case Symbol::Float():
                return  av_.float_as_str(extracted_floats_++);
            case Symbol::Esc():
                return EscAsString();
            default:
                std::string err_msg = make_str("Extract a arg of unknown type: ", arg_symbol);
                throw std::invalid_argument(err_msg.c_str());
        }
    }
private:
    const ArgValue& av_;
    std::size_t extracted_strs_;
    std::size_t extracted_ints_;
    std::size_t extracted_floats_;
};
