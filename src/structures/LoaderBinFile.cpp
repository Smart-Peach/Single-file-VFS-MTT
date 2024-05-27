#include "../includes/LoaderBinFile.hpp"

char LoaderBinFile::read_char(size_t address) {
    // TODO: add address check
    fs_file.seekg(address);
    char ch;
    fs_file.read((char*)&ch,sizeof(ch));
    return ch;
}

void LoaderBinFile::write_char(size_t address, char ch) {
    // TODO: add address check
    fs_file.seekg(address);
    fs_file.write((char*)&ch, sizeof(ch));
}

unsigned int LoaderBinFile::read_int(size_t address) {
    // TODO: add address check
    fs_file.seekg(address);
    unsigned int num;
    fs_file.read((char*)&num,sizeof(num));
    return num;
}

void LoaderBinFile::write_int(size_t address, unsigned int num) {
    // TODO: add address check
    fs_file.seekg(address);
    fs_file.write((char*)&num, sizeof(num));
}

str_t LoaderBinFile::read_string(size_t address) {
    // TODO: add address check
    size_t count = 0;
    char ch = read_char(address + sizeof(char) * (count++));
    str_t line;
    while (ch != '\0' and ch !='\n' and ch != EOF) {
        line += ch;
        ch = read_char(address + sizeof(char) * (count++));
        // TODO: Check for too long string
    }
    return line;
}

void LoaderBinFile::write_string(size_t address, const str_t string) {
    // TODO: add address check
    // Exception for too long string
    for (size_t i = 0; i < string.size(); i++) {
        char ch = string[i];
        write_char(address + sizeof(char) * i, ch);
    }
    write_char(address + sizeof(char) * string.size(), '\0');
}

time_t LoaderBinFile::read_time_t(size_t address) {
    // TODO: check address
    fs_file.seekg(address);
    time_t t;
    fs_file.read((char*)&t,sizeof(t));
    return t;
}

void LoaderBinFile::write_time_t(size_t address, time_t time) {
    // TODO: check address;
    fs_file.seekg(address);
    fs_file.write((char*)&time, sizeof(time));
}

void LoaderBinFile::write_freeblocks(std::vector<bit> free_blocks) {
    char byte;
    size_t bytes_count = 0;
    size_t bits_count = BITS_IN_BYTE;

    for (size_t i = 0; i < free_blocks.size(); i++) {
        bit bit_i = free_blocks[i];
        byte = (byte << 1) + bit_i;
        bits_count--;

        if(!bits_count || i == free_blocks.size() - 1) {
            byte <<= bits_count;
            write_char(SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK + sizeof(char) * (bytes_count++), byte);
            byte = 0;
            bits_count = BITS_IN_BYTE;
        }
    }
}

std::vector<bit> LoaderBinFile::read_freeblocks(int freeblocks_amount) {
    int busy_bytes_amount = freeblocks_amount / BITS_IN_BYTE + (freeblocks_amount % BITS_IN_BYTE ? 1 : 0);
    std::vector<bit> free_blocks(freeblocks_amount);
    int bits_left = freeblocks_amount;

    for (size_t i = 0; i < busy_bytes_amount; i++) {
        char byte = read_char(SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK + sizeof(char) * i);

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
    size_t fs_type_len = sizeof(char) * (superblock.fs_type.size() + 1);
    
    write_string(SIZEOF_BOOT_SECTOR, superblock.fs_type); // WRONG FIELD
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len, superblock.sizeof_fs);
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 1, superblock.max_sizeof_file);
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 2, superblock.sizeof_ilist_bytes);
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 3, superblock.number_blocks);
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 4, superblock.number_free_blocks);
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 5, superblock.number_available_inodes);
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 6, superblock.sizeof_block);
    write_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 7, superblock.size_of_rootdir);

    write_freeblocks(superblock.free_blocks);
}

Superblock LoaderBinFile::unload_superblock() {
    str_t type_fs                 = read_string(SIZEOF_BOOT_SECTOR);
    int fs_type_len = (type_fs.size() + 1) * sizeof(char);

    int   sizeof_fs               = read_int(SIZEOF_BOOT_SECTOR + fs_type_len);
    int   max_sizeof_file         = read_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 1);
    int   sizeof_ilist_bytes      = read_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 2);
    int   number_blocks           = read_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 3);
    int   number_free_blocks      = read_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 4);
    int   number_available_inodes = read_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 5);
    int   sizeof_block            = read_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 6);
    int   size_of_rootdir         = read_int(SIZEOF_BOOT_SECTOR + fs_type_len + sizeof(unsigned int) * 7);

    std::vector free_blocks = read_freeblocks(number_blocks);
    return Superblock(type_fs, sizeof_fs, max_sizeof_file, sizeof_ilist_bytes, number_blocks, number_free_blocks, number_available_inodes, sizeof_block, size_of_rootdir, free_blocks);
}

void LoaderBinFile::load_inode(size_t address, Inode inode) {
    // TODO: check address
    write_int(address, inode.if_directory());
    write_int(address + sizeof(int), inode.get_magic_number());
    write_int(address + sizeof(int) * 2, inode.get_number_of_references());
    write_int(address + sizeof(int) * 3, inode.get_sizeof_file());
    write_int(address + sizeof(int) * 4, inode.get_blocks_amount());
    write_time_t(address + sizeof(int) * 5, inode.get_last_access_time());
    write_time_t(address + sizeof(int) * 5 + sizeof(time_t), inode.get_last_file_modif_time());
    write_time_t(address + sizeof(int) * 5 + sizeof(time_t) * 2, inode.get_last_inode_modif_time());

    size_t shift = address + sizeof(int) * 5 + sizeof(time_t) * 3;
    write_string(shift, inode.get_identifier());
    shift += sizeof(char) * (inode.get_identifier().size() + 1);

    for(size_t block : inode.get_blocks_storage()) {
        write_int(shift + sizeof(int), block);
    }
}

Inode LoaderBinFile::unload_inode(size_t address, size_t sizeof_inode) {
    bool   is_directory      = read_int(address);
    int    magic_number      = read_int(address + sizeof(int));
    int    number_references = read_int(address + sizeof(int) * 2);
    int    sizeof_file       = read_int(address + sizeof(int) * 3);
    int    blocks_amount     = read_int(address + sizeof(int) * 4);

    size_t shift = address + sizeof(int) * 5;

    time_t last_access_time      = read_time_t(shift);
    time_t last_file_modif_time  = read_time_t(shift + sizeof(time_t));
    time_t last_inode_modif_time = read_time_t(shift + sizeof(time_t) * 2);

    shift += sizeof(time_t) * 3;

    str_t identifier = read_string(shift);
    shift += sizeof(char) * (identifier.size() + 1);
    size_t count = 0;
    vector_size_t storage_blocks;
    size_t block = read_int(shift);
    while(block) {
        storage_blocks.push_back(block);
        block = read_int(shift + sizeof(int)*(count++));
    }

    return Inode(is_directory, magic_number, sizeof_file, identifier, blocks_amount, storage_blocks);
}

void LoaderBinFile::load_inode_map(InodeMap mapa, size_t sizeof_freeblocks, size_t sizeof_inode) {
    size_t shift = sizeof_freeblocks + SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK;

    size_t count = 0;
    for (std::pair<const unsigned long, Inode> inode_pair : mapa.inode_map) {
        load_inode(shift + sizeof_inode * (count++), inode_pair.second);
    }
}

InodeMap LoaderBinFile::unload_inode_map(size_t sizeof_ilist, size_t sizeof_freeblocks, size_t sizeof_inode) {
    size_t shift = SIZEOF_BOOT_SECTOR + SIZEOF_SUPERBLOCK + sizeof_freeblocks;
    size_t inodes_amount = sizeof_ilist / sizeof_inode;

    InodeMap mapa;

    for (size_t i=0; i< inodes_amount; i++) {
        Inode inode = unload_inode(shift + sizeof_inode * i, sizeof_inode);
        mapa.add_inode(inode);
    }
    return mapa;
}

void LoaderBinFile::load_rootdir() {
    return;
}

void LoaderBinFile::unload_rootdir() {

}

