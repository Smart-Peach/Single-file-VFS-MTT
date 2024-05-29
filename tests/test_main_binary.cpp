#include <fstream>
#include <iostream>
#include <string>
#include "../src/includes/AwesomeFileSystem.hpp"


int main() {
    Superblock superblock;
    InodeMap map;

    Inode* inode = new Inode();
    Dentry* d = new Dentry("tests/test.bin", inode);
    AwesomeFileSystem fs(superblock, map, "tests/test-file.bin", d);
    fs.create_file("test-file1.txt");
    fs.write_to_file("test-file1.txt", "Hello!!!!!!");
    fs.create_file("test-file2.txt");
    fs.write_to_file("test-file2.txt", "World))))))");
    fs.create_file("test-file3.txt");
    fs.write_to_file("test-file3.txt", "Oh yeah ******");
    fs.read_file("test-file2.txt");
    std::cout<<"hello"<<std::endl;

    std::string str = "";
    for(int i = 0; i < 1024; ++i){
        str += "d";
    }
    fs.write_to_file("test-file2.txt", str);
    // fs.close_file("test-file1.txt");
    return 0;
}