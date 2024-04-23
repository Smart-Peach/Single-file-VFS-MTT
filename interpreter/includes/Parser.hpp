#pragma once 
#include "includes.hpp"
#include <string> 


//TODO: add context as arg / or impl some derived classes of ctx
typedef std::function<Command*()> cmd_cstr_t;
typedef std::vector<std::string> str_vector_t;
typedef std::string str_t;



class Parser {
    Context* context;
    bool exit_flag;
    str_t input_line;
    size_t curr_pos;

    std::map<const str_t, cmd_cstr_t> zero_args_funcs = {
    {"exit", []() { return new Exit(); }}};

    std::map<const str_t, cmd_cstr_t> one_arg_funcs {
    {"create", []() { return new CreateFile(); }},
    {"delete", []() { return new DeleteFile(); }},
    {"edit", []() { return new EditFile(); }},
    {"read", []() { return new ReadFile(); }},
    {"crtdir", []() { return new CreateDir(); }},
    {"deldir", []() { return new DeleteDir(); }},
    {"rdir", []() { return new ReadDir(); }},
    {"ldir", []() { return new LinkDir(); }},
    {"uldir", []() { return new UnlinkDir(); }}};

    std::map<const str_t, cmd_cstr_t> two_args_funcs{
    {"rename", []() { return new RenameFile(); }},
    {"move", []() { return new MoveFile(); }},
    {"rndir", []() { return new RenameDir(); }}};

    std::map<const str_t, cmd_cstr_t> data_arg_funcs {
    {"write", []() { return new WriteFile(); }},
    {"append", []() { return new AppendToFile(); }}};


public:
    Parser(Context* context, str_t input_line):
                            context(context),
                            input_line(input_line),
                            curr_pos(-1),
                            exit_flag(false) { }
    ~Parser() = default;

    Command* next_command();

private:
    static bool contains(const str_t& str, char symbol);
    str_t next_token(size_t sym_pos);
    str_t parse_text(size_t sym_pos);
    Command* parse(str_t token);
    Command* line_parse(str_t token);
    bool is_next_file();
};
