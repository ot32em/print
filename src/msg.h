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
private:
    std::string msg_;
};
