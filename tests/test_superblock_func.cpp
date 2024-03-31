#include <fstream>
#include <iostream>
#include <string>

#include "../src/includes/Superblock.hpp"

using namespace std;

int main() {
    std::fstream file;
    file.open("test.bin", std::ios_base::out | std::ios_base::binary);
    if(!file.is_open())
    {
        std::cout<<"Unable to open the file\n";
        return 0;
    }
    Superblock superblock;
    superblock.load_into_memory(file);


    // file << "3333345";
    file.close();
}
