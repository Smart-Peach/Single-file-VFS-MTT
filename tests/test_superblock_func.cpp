#include <fstream>
#include <iostream>

#include "../src/includes/AwesomeFileSystem.hpp"

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
    InodeMap map;

    AwesomeFileSystem fs(superblock, map, "tests/test.bin");

    fs.load_superblock_into_memory();
    // superblock.load_into_memory(file);
    // superblock.load_from_memory(file);

    // superblock.print();


    // file << "3333345";
    file.close();
}
