
#include <string>
#include <vector>
#include "../interpretor/Interpretor.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <bits/stdc++.h>

typedef std::vector<std::string> str_args_t;


TEST(InterpretorGTest, writeCommand){
    str_args_t all_args{"write", "test_file.py"};
    std::string excpected = "file test_file.py written";
    std::cout << "Excpected:\n" << excpected << std::endl;
    std::cout << "Actual:" << std::endl;
    Interpretor* interpretor = new Interpretor(all_args);
    interpretor->interpret();
}


int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}