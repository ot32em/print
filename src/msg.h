class Msg
{public:
    Msg(const char* msg)
        :msg_(msg)
    {}

    void add(const char* str)
    {
    };

    std::string str() const
    {
        return msg_;
    }

    std::size_t count_format_count() const { return 0; }

private:
    std::string msg_;
};
