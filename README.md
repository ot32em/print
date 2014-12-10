#TODO:

## Description and TODO checkbox

[ ] `print::f` - A type-safe printf like function.
> `print::f(std::ostream&, const char* msg, args...)`

[ ] `print::c` - A `print::f` with replacing std::ostream with `std::cout`, less typing.
> `print::c(const char* msg, ...)`

[ ] `print::d` - A `print::f` with pure result message to `OutputDebugString`. Very usefull for Windows Developing.
> `print::d(const char* msg, ...)`

## Usage

``` cpp
print::f(std::cout, "My cat is named %s. %s is %d years old." 
    "Nini", std::string("Nini"), 5);
// print `My cat is named Nini. Nini is 5 years old` into std::cout

print::c("%s eats food %f pounds every day. And %s fat rate is %f%%",
    "Nini", 3.14, "her", 20.0);
// print `Nini eats food 3.14 pounds every day. And her fat rate is 20.0%` on std::cout 

print::d("[Log] name: %s, age: %d, fat rate: %f\n",
    username(), get_age(), get_fatrate());
// equals OutputDebugString("[Log] name: OT, age: 99, fat rate 25\n");
```

## Format Symbol

 - %s: expect string 
    - `std::string`
    - `const char*`

 - %d: expect integer
    - bool
    - short
    - int
    - ...
    - to long long 
    - builtin integers.

 - %f: expect floating integers
    - float
    - double
    - long double

 - %%: a escape symbol to represent %


## Error Handling

1. Any wrong type arguments as wrong position causes compile error.

    ```cpp
    print::c("I'm %s.", 123); // static_assert complains arg1(%s) expects string
    ```

2. Any wrong amount arguments on given message causes compile error.
    
    ```cpp
    print::c("I'm %s. You're %s", "OT"); // static_assert complains missing arg2.
    ```

3. Any unrecongized format symbol e.g. %g %a causes compile error.

    ```cpp
    print::c("I'm %a", "OT"); // static_assert complains unknown symbol
    ```

## Limitation
  
  - Msg must be a string literal for compile-time arguments amount and type checking.

    ```cpp
    print::c(std::string("Herher! %s!"), "HAHA"); // gg

    ```

## Run Test

```bash run behavior tests
/path/to/print_root> $ make btest 
```

```bash run unit tests
/path/to/print_root> $ make utest 
```

## exp zone

``` bash
/path/to/print_root> $ vi src/exp.cpp
/path/to/print_root> $ make exp
```
