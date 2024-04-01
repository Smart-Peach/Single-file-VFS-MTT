#include <fstream>
#include <iostream>
#include <string>

#include "../src/includes/Superblock.hpp"

using namespace std;

int main() {
    std::fstream file;
    file.open("tests/test.bin", std::ios_base::out | std::ios_base::binary);
    if(!file.is_open())
    {
        std::cout<<"Unable to open the file\n";
        return 0;
    }
    Superblock superblock;
    superblock.load_into_memory(file);
    superblock.load_from_memory(file);
    superblock.print();


    // file << "3333345";
    file.close();
}
