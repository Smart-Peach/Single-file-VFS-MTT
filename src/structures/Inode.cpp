#include <iostream>
#include <vector>
#include "../includes/Inode.hpp"

// Maybe another type
const std::vector<size_t>& Inode::get_storage_blocks() {  
    return storage_blocks;
}

size_t Inode::get_last_block(){
    return storage_blocks[-1];
}

// Print all fields of inode 
void Inode::print_fields() { 
    std::cout << "Magic number of inode = " << magic_number << std::endl;
    std::cout << "optional_bit1 = " << optional_bit1 << std::endl;
    std::cout << "optional_bit2 = " << optional_bit2 << std::endl;
    std::cout << "Number of references to file = " << number_references << std::endl;
    std::cout << "Identificator of owner/user and group-owner = " << identifier << std::endl;
    std::cout << "Current sizeof file = " << sizeof_file << std::endl;
    std::cout << "Time of the last access to the file = " << last_access_time << std::endl;
    std::cout << "Time of the last file modification = " << last_file_modif_time << std::endl;
    std::cout << "Time of the last inode modification = " << last_inode_modif_time << std::endl;
    std::cout << "Current sizeof array with storage block addresses = " << blocks_amount << std::endl;
    std::cout << "Array of storage block addresses: ";
    for(int i = 0; i < blocks_amount; i++) std::cout << storage_blocks[i] << " ";
}


int Inode::get_sizeof_file() {
    return sizeof_file;
}

int Inode::get_magic_number() {
    return magic_number;
}

int Inode::get_blocks_amount() {
    return blocks_amount;
}

void Inode::increase_blocks_amount(){
    blocks_amount += 1;
}

void Inode::add_size_to_sizeof_file(int add_size){
    sizeof_file += add_size;
}

void Inode::update_storage_blocks(size_t address){
    storage_blocks.push_back(address);
}
