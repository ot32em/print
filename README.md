TODO:

    Usage like:

    print(std::cout, "My cat is named %. % is % years old. Eat % pound food per day", 
        "Nini", std::string("Nini"), 5, 3.14);


    Three functions:

    - print(ostream&, const char* format_str, args...)

    - cprint(msg, ...) 
        > like  print(std::cout, msg, ...)

    - dprint(msg, ...)
        > write stream to OutputDebugString(Windows only)
