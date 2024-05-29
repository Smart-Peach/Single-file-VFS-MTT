#include "../includes/Crypter.hpp"

int& Crypter::get_key_for_encryption(){
    return key_for_encryption;
}

// here we have to encrypt the data from the user or write the pre-encrypted data to a file
str_t Crypter::data_encryption(str_t data){
    str_t str = "";
    for(int i = 0; i < data.size(); i++){
        str += data[i] + key_for_encryption;
    }
    return str;
}

// here we have to decrypt the data from the file system that the user asked for
str_t Crypter::data_decryption(str_t data){
    str_t str = "";
    for(int i = 0; i < data.size(); i++){
        str += data[i] + key_for_decryption;
    }
    return str;

}

//generate pair for key_encryption and key_decryption
std::pair<int, int> Crypter::generate_keys(){
    int key = rand() % 10;
    return std::pair<int, int> {key, -key};
}