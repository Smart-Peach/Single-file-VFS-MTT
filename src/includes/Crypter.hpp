#pragma once
#include "types.hpp"
#include <cstdlib>


class Crypter{
    //TODO: we need str_t type, not int
    int key_for_decryption; //the key to decrypt the FS data 
public:
    int key_for_encryption; //the key for encrypting the data coming from the user
    int& get_key_for_encryption();
    str_t data_encryption(str_t data); //function for encrypting incoming data
    str_t data_decryption(str_t data); //a function for decrypting data from the file system
    std::pair<int, int> generate_keys(); // function which generate keys for work with data
    Crypter(){
        std::pair<int, int> keys = generate_keys();
        key_for_encryption = keys.first;
        key_for_decryption = keys.second;
    };
};