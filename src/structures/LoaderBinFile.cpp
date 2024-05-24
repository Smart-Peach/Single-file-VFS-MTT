#include "../includes/LoaderBinFile.hpp"

char LoaderBinFile::read_char(size_t address) {
    fs_file.seekg(address);
    char ch;
    fs_file.read((char*)&ch,sizeof(ch));
    return ch;
}

void LoaderBinFile::write_char(size_t address, char ch) {
    fs_file.seekg(address);
    fs_file.write((char*)&ch, sizeof(ch));
}

unsigned int LoaderBinFile::read_int(size_t address) {
    fs_file.seekg(address);
    unsigned int num;
    fs_file.read((char*)&num,sizeof(num));
    return num;
}

void LoaderBinFile::write_int(size_t address, unsigned int num) {
    fs_file.seekg(address);
    fs_file.write((char*)&num, sizeof(num));
}

const char* LoaderBinFile::read_constchar(size_t address) {

}

std::vector<bool> LoaderBinFile::read_freeblocks() {
    fs_file.seekg(SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK);
    std::vector<bool> blocks {false, false, false};
    return blocks;
}

void LoaderBinFile::write_constchar(size_t address, const char* string) {
    
}

void LoaderBinFile::write_freeblocks(std::vector<bool> free_blocks) {

}

void LoaderBinFile::load_superblock(Superblock superblock) {
    fs_file.seekg(SIZEOF_BOOT_SECTOR);

    write_int(SIZEOF_BOOT_SECTOR, superblock.sizeof_fs); // WRONG FIELD
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int), superblock.sizeof_fs);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 2, superblock.max_sizeof_file);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 3, superblock.sizeof_ilist_bytes);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 4, superblock.number_blocks);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 5, superblock.number_free_blocks);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 6, superblock.number_available_inodes);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 7, superblock.sizeof_block);
    write_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 8, superblock.size_of_rootdir);

    // write_bitset(superblock.free_blocks);
}

Superblock LoaderBinFile::unload_superblock() {
    fs_file.seekg(SIZEOF_BOOT_SECTOR);

    int type_fs                 = read_int(SIZEOF_BOOT_SECTOR); // WRONG FIELD
    int sizeof_fs               = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int));
    int max_sizeof_file         = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 2);
    int sizeof_ilist_bytes      = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 3);
    int number_blocks           = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 4);
    int number_free_blocks      = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 5);
    int number_available_inodes = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 6);
    int sizeof_block            = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 7);
    int size_of_rootdir         = read_int(SIZEOF_BOOT_SECTOR + sizeof(unsigned int) * 8);

    // std::bitset<> bitset = read_bitset();
    std::vector free_blocks = read_freeblocks();
    const char* string = "linear";
    return Superblock(string, sizeof_fs, max_sizeof_file, sizeof_ilist_bytes, number_blocks, number_free_blocks, number_available_inodes, sizeof_block, size_of_rootdir, free_blocks);
}

void LoaderBinFile::load_inode_map() {

}

void LoaderBinFile::load_rootdir() {
    return;
}

void LoaderBinFile::unload_inode_map() {

}

void LoaderBinFile::unload_rootdir() {

}

