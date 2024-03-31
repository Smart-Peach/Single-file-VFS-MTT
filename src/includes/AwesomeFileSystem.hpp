#include "FileSystem.hpp"

class AwesomeFileSystem: public FileSystem{
public:
    ~FileSystem();
    void write_to_file(string, string);
    void open_file(string);
    void read_file(string);
    void upload_to_file(string);
    // TODO: should it take name of the file to open or (mb) already opened file?
    FileSystem(Superblock, bitset_t, InodeMap, str_t);
}