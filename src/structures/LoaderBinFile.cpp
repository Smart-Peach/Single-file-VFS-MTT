#pragma once

#include "../includes/LoaderBinFile.hpp"

char LoaderBinFile::read_char(size_t address) {
    fs_file.seekg(address);
    char ch;
    fs_file.read((char*)&ch,sizeof(ch));
    return ch;
}

int LoaderBinFile::read_int(size_t address) {
    fs_file.seekg(address);
    unsigned int num;
    fs_file.read((char*)&num,sizeof(num));
    return num;
}

void LoaderBinFile::write_int(size_t address, unsigned int num) {
    fs_file.seekg(address);
    fs_file.write ((char*)&num, sizeof(num));
}

void LoaderBinFile::write_char(size_t address, char ch) {
    fs_file.seekg(address);
    fs_file.write ((char*)&ch, sizeof(ch));
}

bitset<> LoaderBinFile::read_bitset() {

}

void LoaderBinFile::load_superblock(Superblock superblock) {
    fs_file.seekg(SIZEOF_BOOT_SECTOR);

    write_int(SIZEOF_BOOT_SECTOR, superblock.sizeof_fs);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int), superblock.sizeof_fs);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int)*2, superblock.sizeof_fs);
}

void LoaderBinFile::load_inode_map() {

}

void LoaderBinFile::load_rootdir() {

}

void LoaderBinFile::unload_superblock() {

}

void LoaderBinFile::unload_inode_map() {

}

void LoaderBinFile::unload_rootdir() {

}

