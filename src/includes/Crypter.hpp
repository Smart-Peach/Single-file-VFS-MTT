#pragma once
#include "types.hpp"
class Crypter{
    str_t key_for_decryption; //the key to decrypt the FS data
public:
    str_t key_for_encryption; //the key for encrypting the data coming from the user
    str_t& get_key_for_encryption();
    void data_encryption(str_t src_name, str_t data); //function for encrypting incoming data
    str_t& data_decryption(str_t src_name); //a function for decrypting data from the file system
};