#include "../includes/Cryptographer.hpp"

str_t& Cryptographer::get_key_for_encryption(){
    return key_for_encryption;
}

void Cryptographer::data_encryption(str_t src_name){
    // here we have to encrypt the data from the user or write the pre-encrypted data to a file
}
str_t& Cryptographer::data_decryption(str_t src_name){
    // here we have to decrypt the data from the file system that the user asked for
}
