clear
mkdir -p build
g++ --std=c++11 test_runner.cpp  -I../main -o build/tester.out
build/tester.out
