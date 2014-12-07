#include "print.h"
#include "MessageFormat.h"
#include <iostream>
#include <sstream>


template<typename T>
void check_eq(const T& actual, const T& expected, const char* msg)
{
    if(actual != expected)
    {
        std::cerr << "\nFailure. Case: " << msg << ". value should be " << expected << ", actual: " << actual << std::endl;
    }
    else
    {
        std::cerr << ".";
    }
}

void check_eq(const std::ostringstream& result_out, const std::string& expected, const char* msg)
{
    check_eq(result_out.str(), expected, msg);
}

void check_eq(const MessageFormat& mf, const std::string& expected, const char* msg)
{
    check_eq(mf.str(), expected, msg);
}

int main()
{
    typedef std::ostringstream ostr;
    {
        {
            ostr out;
            print(out, "Hello world.");
            check_eq(out, "Hello world.", "plain_text");
        }
        {
            ostr out;
            print(out, "Hello %.", "world");
            check_eq(out, "Hello world.", "replace one string");
        }
        /*
        {
            ostr out;
            print(out, "Hello %. I am %.", "world", "OT");
            check_eq(out, "Hello world. I am OT.");
        }
        */
        {
            const char* msg = "Hello";
            {
                MessageFormat mf(msg);
                check_eq(mf, "Hello", "MsgFormat no args");
                check_eq(mf.args_count(), (std::size_t)0, "MsgFormat args should be 0");
            }
        }
    }
    std::cout << "\ntest finishes.\n";
    return 0;
}
