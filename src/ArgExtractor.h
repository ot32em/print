#pragma once

#include "ArgValue.h"

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
            case 's': 
                return av_.str_as_str(extracted_strs_++);
            case 'd': 
                return av_.int_as_str(extracted_ints_++);
            case 'f':
                return  av_.float_as_str(extracted_floats_++);
            case '%':
                return "%";
            default:
                std::string err_msg = std::string("detected type: ") + "[" + type + "]";
                err_msg += ". extract a unknown type arg.";
                throw std::invalid_argument(err_msg.c_str());
        }
    }
private:
    const ArgValue& av_;
    std::size_t extracted_strs_;
    std::size_t extracted_ints_;
    std::size_t extracted_floats_;
};
