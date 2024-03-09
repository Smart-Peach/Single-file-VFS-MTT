#pragma once 
#iclude "Function.hpp"

class Parser(): public Function{
public:
    void create_file();
    void delete_file();
    void edit_file();
    void read_file();
    void write_file();
    void append_file();
    void seek_file();
    void rename_file();
    void move_file();

private:
    void next_command();
    void parse();
}
