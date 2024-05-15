#include <fstream>
#include <iostream>
#include <string>
#include "../src/includes/AwesomeFileSystem.hpp"

void testing(std::fstream &file) {
    file.seekg(5);
    file << "start";
}

// int read_int(std::fstream &fs_file, size_t address) {
//     fs_file.seekg(address);
//     int i;
//     fs_file.read((char*)&i,sizeof(int));
//     // fs_file >> i;
//     return i;
// }

void write_int(std::fstream &fs_file, size_t address, unsigned int num) {
    fs_file.seekg(address);
    fs_file.write ((char *)&num, sizeof(num));
}

int read_int(std::fstream &fs_file, size_t address) {
    fs_file.seekg(address);
    unsigned int num;
    fs_file.read((char*)&num,sizeof(num));
    return num;
}

int main() {
    std::fstream fs_file;
    fs_file.open("tests/test-seek.bin", std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    fs_file << "000000000000000000000000000000000000000000000000000";
    // testing(fs_file);
    fs_file.seekg(0);
    // fs_file << 33333;
    // int num1 = 32000;
    // int num2 = 555;
    // int num3 = 78888;
    // fs_file.write ((char *)&num1, sizeof(num1));
    // fs_file.write ((char *)&num2, sizeof(num2));
    // fs_file.write ((char *)&num3, sizeof(num3));
    // int number = read_int(fs_file, 0);
    // std::cout << typeid(number).name()   << std::endl;
    // std::cout << read_int(fs_file, 0) << "\n";
    // std::cout << read_int(fs_file, 4) << "\n";
    // std::cout << read_int(fs_file, 8) << "\n";
    write_int(fs_file, 5, 1073741824);
    std::cout << read_int(fs_file, 5) << std::endl;
}