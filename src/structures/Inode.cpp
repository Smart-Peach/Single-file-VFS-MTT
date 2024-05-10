#include <iostream>
#include <vector>
#include "../includes/Inode.hpp"

Inode::Inode(bool src_type):
            is_directory(src_type),
            number_references(0),
            sizeof_file(0),
            last_access_time(time(nullptr)),
            last_file_modif_time(time(nullptr)),
            last_inode_modif_time(time(nullptr)),
            blocks_amount(1) { }


Inode::Inode(bool src_type, size_t address_block):
            is_directory(src_type),
            number_references(0),
            sizeof_file(0),
            last_access_time(time(nullptr)),
            last_file_modif_time(time(nullptr)),
            last_inode_modif_time(time(nullptr)),
            blocks_amount(1)
{
    blocks_storage.push_back(address_block);
}

// Maybe another type
const std::vector<size_t>& Inode::get_blocks_storage() {  
    return blocks_storage;
}

size_t Inode::get_last_block(){
    return blocks_storage.back();
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
    for(int i = 0; i < blocks_amount; i++) std::cout << blocks_storage[i] << " ";
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

void Inode::update_blocks_storage(size_t address){
    blocks_storage.push_back(address);
}

void Inode::increase_references_amount() {
    number_references++;
}

void Inode::decrease_references_amount(){
    number_references--;
}

//Update info in file's inode after adding one block
void Inode::update_inode(int size, int new_address){
    increase_blocks_amount();
    add_size_to_sizeof_file(size);
    update_blocks_storage(new_address);
}

void Inode::update_last_access_time(){
    time(&last_access_time);
}

void Inode::update_last_file_and_inode_modif_fields(){
    time(&last_file_modif_time);
    time(&last_inode_modif_time);
}