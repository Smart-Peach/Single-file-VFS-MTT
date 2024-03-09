#pragma once 


void create_file();
void delete_file();
void edit_file();
void read_file();
void write_file();
void append_file();
void seek_file();
void rename_file();
void move_file();

struct fileCmds = {
            ._create = &create_file,
            ._delete = &delete_file,
            ._edit = &edit_file,
            ._read = &read_file,
            ._write = &write_file,
            ._append = &append_file,
            ._seek = &seek_file,
            ._rename = &rename_file,
            ._move = &move_file
            };