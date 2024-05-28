#include "../includes/LoaderBinFile.hpp"

/// @brief Reads char (byte) from binary file and shifts address by sizeof char
/// @param address in bytes
char LoaderBinFile::read_char(size_t& address) {
    // TODO: add address check
    fs_file.seekg(address);
    char ch;
    fs_file.read((char*)&ch,sizeof(ch));
    address += sizeof(char);
    return ch;
}

/// @brief Writes char to binary file and moves address by sizeof char
/// @param address in bytes
void LoaderBinFile::write_char(size_t& address, char ch) {
    // TODO: add address check
    fs_file.seekg(address);
    fs_file.write((char*)&ch, sizeof(ch));
    address += sizeof(char);
}

/// @brief Reads type int from binary file and shifts address by 4 bytes
/// @param address in bytes
unsigned int LoaderBinFile::read_int(size_t& address) {
    // TODO: add address check
    fs_file.seekg(address);
    unsigned int num;
    fs_file.read((char*)&num,sizeof(num));
    address += sizeof(int);
    return num;
}

/// @brief Writes unsigned int to binary type and shifts the address by 4 bytes
/// @param address address in bytes 
void LoaderBinFile::write_int(size_t& address, unsigned int num) {
    // TODO: add address check
    fs_file.seekg(address);
    fs_file.write((char*)&num, sizeof(num));
    address += sizeof(int);
}

/// @brief Writes std::string to address and shifts address by length of string + 1 (because of '\0')
/// @param address in bytes
/// @return std::string without '\0' at the end
str_t LoaderBinFile::read_string(size_t& address) {
    // TODO: add address check
    size_t count = 0;
    char ch = read_char(address);
    str_t line;
    while (ch != '\0' and ch !='\n' and ch != EOF) {
        line += ch;
        ch = read_char(address);
        // TODO: Check for too long string
    }
    return line;
}

/// @brief Writes string to binary file and adds at the end '\0' char. Moves address by length of string + 1
/// @param address address in bytes
/// @param string string without '\0' at the end
void LoaderBinFile::write_string(size_t& address, const str_t string) {
    // TODO: add address check
    // Exception for too long string
    for (size_t i = 0; i < string.size(); i++) {
        char ch = string[i];
        write_char(address, ch);
    }
    write_char(address, '\0');
}

/// @brief Reads time_t type from address and shifts address by sizeof time_t
/// @param address in bytes
/// @return time_t from std
time_t LoaderBinFile::read_time_t(size_t& address) {
    // TODO: check address
    fs_file.seekg(address);
    time_t t;
    fs_file.read((char*)&t,sizeof(t));
    address += sizeof(time_t);
    return t;
}

/// @brief Writes type time_t to binary file and shift address by sizeof time_t
/// @param address in bytes
/// @param time time_t from std
void LoaderBinFile::write_time_t(size_t& address, time_t time) {
    // TODO: check address;
    fs_file.seekg(address);
    fs_file.write((char*)&time, sizeof(time));
    address += sizeof(time_t);
}

void LoaderBinFile::write_freeblocks(std::vector<bit> free_blocks) {
    char byte;
    size_t bits_count = BITS_IN_BYTE;
    size_t address = SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK;

    for (size_t i = 0; i < free_blocks.size(); i++) {
        bit bit_i = free_blocks[i];
        byte = (byte << 1) + bit_i;
        bits_count--;

        if(!bits_count || i == free_blocks.size() - 1) {
            byte <<= bits_count;
            write_char(address, byte);
            byte = 0;
            bits_count = BITS_IN_BYTE;
        }
    }
}

std::vector<bit> LoaderBinFile::read_freeblocks(int freeblocks_amount) {
    int busy_bytes_amount = freeblocks_amount / BITS_IN_BYTE + (freeblocks_amount % BITS_IN_BYTE ? 1 : 0);
    std::vector<bit> free_blocks(freeblocks_amount);
    int bits_left = freeblocks_amount;
    size_t address = SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK;

    for (size_t i = 0; i < busy_bytes_amount; i++) {
        char byte = read_char(address);

        for (size_t j = 0; j < BITS_IN_BYTE; j++) {
            bit curr_bit = byte & 0b10000000;
            byte <<= 1;
            free_blocks[i * BITS_IN_BYTE + j] = curr_bit;
            bits_left--;
            if (!bits_left) {
                break;
            }
        }
    }
    return free_blocks;
}

void LoaderBinFile::load_superblock(Superblock superblock) {
    size_t address = SIZEOF_BOOT_SECTOR;

    write_string(address, superblock.fs_type);
    write_int(address, superblock.sizeof_fs);
    write_int(address, superblock.max_sizeof_file);
    write_int(address, superblock.sizeof_ilist_bytes);
    write_int(address, superblock.number_blocks);
    write_int(address, superblock.number_free_blocks);
    write_int(address, superblock.number_available_inodes);
    write_int(address, superblock.sizeof_block);
    write_int(address, superblock.size_of_rootdir);
    write_freeblocks(superblock.free_blocks);
}

Superblock LoaderBinFile::unload_superblock() {
    size_t address = SIZEOF_BOOT_SECTOR;

    str_t type_fs                 = read_string(address);
    int   sizeof_fs               = read_int(address);
    int   max_sizeof_file         = read_int(address);
    int   sizeof_ilist_bytes      = read_int(address);
    int   number_blocks           = read_int(address);
    int   number_free_blocks      = read_int(address);
    int   number_available_inodes = read_int(address);
    int   sizeof_block            = read_int(address);
    int   size_of_rootdir         = read_int(address);
    std::vector free_blocks       = read_freeblocks(number_blocks);

    return Superblock(type_fs, sizeof_fs, max_sizeof_file, sizeof_ilist_bytes, number_blocks, number_free_blocks, number_available_inodes, sizeof_block, size_of_rootdir, free_blocks);
}

void LoaderBinFile::load_inode(size_t& address, Inode& inode, size_t sizeof_inode) {
    // TODO: check address
    // size_t shift = address;
    size_t address_start = address;

    write_int(address, inode.if_directory());
    write_int(address, inode.get_magic_number());
    write_int(address, inode.get_sizeof_file());
    write_int(address, inode.get_blocks_amount());

    write_time_t(address, inode.get_last_access_time());
    write_time_t(address, inode.get_last_file_modif_time());
    write_time_t(address, inode.get_last_inode_modif_time());

    write_string(address, inode.get_identifier());

    for(size_t block : inode.get_blocks_storage()) {
        write_int(address, block);
    }
    address = address_start + sizeof_inode;
}

Inode LoaderBinFile::unload_inode(size_t& address, size_t sizeof_inode) {
    size_t address_start = address;

    bool   is_directory  = read_int(address);
    int    magic_number  = read_int(address);
    int    sizeof_file   = read_int(address);
    int    blocks_amount = read_int(address);

    time_t last_access_time      = read_time_t(address);
    time_t last_file_modif_time  = read_time_t(address);
    time_t last_inode_modif_time = read_time_t(address);

    str_t identifier = read_string(address);

    vector_size_t storage_blocks;
    size_t block = read_int(address);
    while(block) {
        storage_blocks.push_back(block);
        block = read_int(address);
    }

    address = address_start + sizeof_inode;
    return Inode(is_directory, magic_number, sizeof_file, identifier, blocks_amount, storage_blocks);
}

void LoaderBinFile::load_inode_map(InodeMap mapa, size_t sizeof_freeblocks, size_t sizeof_inode) {
    size_t address = sizeof_freeblocks + SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK;

    for (std::pair<const unsigned long, Inode> inode_pair : mapa.inode_map) {
        load_inode(address, inode_pair.second, sizeof_inode);
    }
}

InodeMap LoaderBinFile::unload_inode_map(size_t sizeof_ilist, size_t sizeof_freeblocks, size_t sizeof_inode) {
    size_t address = SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK + sizeof_freeblocks;
    size_t inodes_amount = sizeof_ilist / sizeof_inode;

    InodeMap mapa;

    for (size_t i = 0; i < inodes_amount; i++) {
        Inode inode = unload_inode(address, sizeof_inode);
        mapa.add_inode(inode);
    }
    return mapa;
}

void LoaderBinFile::load_rootdir() {
    return;
}

void LoaderBinFile::unload_rootdir() {

}

