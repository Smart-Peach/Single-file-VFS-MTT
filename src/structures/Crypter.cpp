#include "../includes/Crypter.hpp"

str_t& Crypter::get_key_for_encryption(){
    return key_for_encryption;
}

void Crypter::data_encryption(str_t src_name, str_t data){
    // here we have to encrypt the data from the user or write the pre-encrypted data to a file
}
str_t& Crypter::data_decryption(str_t src_name){
    // here we have to decrypt the data from the file system that the user asked for
}
