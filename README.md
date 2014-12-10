#TODO:

## Usage like:

``` cpp
print(std::cout, "My cat is named %. % is % years old. Eat % pounds food per day", 
    "Nini", std::string("Nini"), 5, 3.14);
```

``` bash
My cat is named Nini. Nini is 5 years old. eat 3.14 pounds food per day.
```

## Three functions:

- `print(std::ostream&, const char* msg, args...)`

- `cprint(msg, ...)`
    > like  print(std::cout, msg, ...)

- dprint(msg, ...)
    > write stream to OutputDebugString(Windows only)
 
  - Need implement a basic_streambuf.

## Limitation
  
  - msg must be a string literal for compile-time arguments amount and type checking.
