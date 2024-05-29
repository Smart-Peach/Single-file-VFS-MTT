#pragma once

// #include <bitset>
#include <vector>
#include <string>

const int SIZEOF_BOOT_SECTOR = 1024;
const int SIZEOF_SUPERBLOCK = 1024;
static const size_t BLOCKS_AMOUNT = 10000;
static const int BITS_IN_BYTE = 8;

typedef std::string str_t;
typedef bool bit;
typedef std::vector<size_t> vector_size_t;