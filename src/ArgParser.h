#pragma once
#include "cstr.h"
#include "cargseq.h"
#include "ArgType.h"

class ArgParser
{public:

    ArgParser(cstr msg)
        :msg_(msg)
    {
        parse();
    }
    
    void parse()
    {
        seq_t all_seq = arg_seq(msg_, Symbol::Any());
        seq_t str_seq = arg_seq(msg_, Symbol::Str());
        seq_t int_seq = arg_seq(msg_, Symbol::Int());
        seq_t float_seq = arg_seq(msg_, Symbol::Float());
        seq_t escape_seq = arg_seq(msg_, Symbol::Esc());

        arg_tokens_.resize(count_bit1(all_seq));
        for(std::size_t i = 0; i < arg_tokens_.size(); i++)
        {
            arg_tokens_[i].symbol = arg_type_at_bit(i, str_seq, Symbol::Str(),
                                                     int_seq, Symbol::Int(),
                                                     float_seq, Symbol::Float(),
                                                     escape_seq, Symbol::Esc());
            assert(arg_tokens_[i].symbol != Symbol::Unknown() && "Detected unknown symbol when ArgParser parsing.");
            arg_tokens_[i].pos = pos_of_nth_arg(msg_, i);
        }
    }

    std::size_t count_args(char arg_symbol=Symbol::Any()) const
    {
        if(arg_symbol == Symbol::Any()) { return arg_tokens_.size(); }

        return std::count_if(
            arg_tokens_.begin(), 
            arg_tokens_.end(), 
            [arg_symbol](const ArgToken& arg){ return arg.symbol == arg_symbol; });
    };

    std::size_t next_nonescape_arg_i(std::size_t next_i = 0) const
    { 
        for(std::size_t i = next_i; i != arg_tokens_.size(); i++) 
        {
            if(arg_tokens_.at(i).symbol != Symbol::Esc())
            {
                return i;
            }
        }
        throw std::invalid_argument("No more non escape arg.");
    }

    ArgToken operator[](std::size_t i) const
    {
        return arg_tokens_.at(i);
    }

    std::vector<ArgToken>::iterator begin() { return arg_tokens_.begin(); }
    std::vector<ArgToken>::iterator end() { return arg_tokens_.end(); }

    std::vector<ArgToken>::const_iterator begin() const { return arg_tokens_.begin(); }
    std::vector<ArgToken>::const_iterator end() const { return arg_tokens_.end(); }

    std::vector<ArgToken> arg_tokens() const { return arg_tokens_; }

private:
    cstr msg_;
    std::vector<ArgToken> arg_tokens_;
};


