#include <fstream>
#include <iostream>
#include <string>
#include "../src/includes/AwesomeFileSystem.hpp"


int main() {
    std::fstream file;
    file.open("test.bin", std::ios_base::out | std::ios_base::binary);
    if(!file.is_open())
    {
        std::cout<<"Unable to open the file\n";
        return 0;
    }
    std::string myStr = "This string is written to the binary file.";
    Superblock superblock;
    InodeMap map;

    AwesomeFileSystem fs(superblock, map, "tests/test-file.bin");
    fs.create_file("test-file1.txt");
    fs.write_to_file("test-file1.txt", "Hello!!!!!!");
    // << : redirects input to file
    // >> : redirects output from file to ...
    //file << myStr;

    // Set position in input sequence
    file.seekg(0);
    file << "!!!!";
    file << "??";
    file.close();
    return 0;
}