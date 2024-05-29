#include <fstream>
#include <iostream>
#include <string>
#include "../src/includes/Crypter.hpp"

int main() {
    Crypter crp = Crypter();
    str_t str = "ABCDEF";
    std::cout<<crp.data_decryption(crp.data_encryption(str));
}