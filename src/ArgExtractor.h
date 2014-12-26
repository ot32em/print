#pragma once

#include "ArgValue.h"
#include "make_str.h"

class ArgExtractor
{public:
    ArgExtractor(const ArgValue& av)
        :av_(av),
        extracted_strs_(0),
        extracted_ints_(0),
        extracted_floats_(0)
    {}

    std::string extract_next(char type)
    {
        switch(type)
        {
            case symbol::Str(): 
                return av_.str_as_str(extracted_strs_++);
            case symbol::Int(): 
                return av_.int_as_str(extracted_ints_++);
            case symbol::Float():
                return  av_.float_as_str(extracted_floats_++);
            case symbol::Esc():
                return EscAsString();
            default:
                std::string err_msg = make_str("Extract a arg of unknown type: ", type);
                throw std::invalid_argument(err_msg.c_str());
        }
    }
private:
    const ArgValue& av_;
    std::size_t extracted_strs_;
    std::size_t extracted_ints_;
    std::size_t extracted_floats_;
};
