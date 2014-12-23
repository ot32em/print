#pragma once

class ArgValue
{public:
    ArgValue(std::size_t str_count, std::size_t int_count, std::size_t float_count)
        : 
        str_values_(str_count), int_values_(int_count), float_values_(float_count),
        added_strs_(0), added_ints_(0), added_floats_(0) {}

    void add(const char* s) 
    { 
        str_values_.at(added_strs_++) = s; 
    }
    void add(int v) 
    {
        int_values_.at(added_ints_++) = v; 
    }
    void add(double v) 
    { 
        float_values_.at(added_floats_++) = v; 
    }

    std::string str_as_str(std::size_t nth) const 
    { 
        return str_values_[nth];
    }
    
    std::string int_as_str(std::size_t nth) const 
    { 
        return std::to_string(int_values_[nth]);
    }

    std::string float_as_str(std::size_t nth) const 
    { 
        char buf[32] = {};
        float val = float_values_[nth];
        sprintf(buf, "%.1f", val);
        return buf;
    }

private:
    std::vector<std::string> str_values_;
    std::size_t added_strs_;

    std::vector<unsigned long long> int_values_;
    std::size_t added_ints_;

    std::vector<double> float_values_;
    std::size_t added_floats_;
};
