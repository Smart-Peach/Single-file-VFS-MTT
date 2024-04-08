
#include <string>
#include <vector>
#include "../iinterpreter/Interpreter.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <bits/stdc++.h>

typedef std::vector<std::string> str_args_t;


TEST(InterpreterGTest, writeFileCommand){
    str_args_t all_args{"write", "test_file.py"};
    std::string excpected = "file test_file.py written";
    std::cout << "Excpected:\n" << excpected << std::endl;
    std::cout << "Actual:" << std::endl;
    Interpreter* iinterpreter = new Interpreter(all_args);
    iinterpreter->interpret();
    delete iinterpreter;
}

TEST(InterpreterGTest, UnlinkDirCommand){
    str_args_t all_args{"uldir", "nice-dir"};
    std::string excpected = "directory nice-dir unlinked";
    std::cout << "Excpected:\n" << excpected << std::endl;
    std::cout << "Actual:" << std::endl;
    Interpreter* iinterpreter = new Interpreter(all_args);
    iinterpreter->interpret();
    delete iinterpreter;
}


int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}