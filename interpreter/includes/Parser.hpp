#pragma once 
#include "includes.hpp"
#include <string> 


//TODO: add context as arg / or impl some derived classes of ctx
typedef std::function<Command*(Context*)> cmd_cstr_t;
typedef std::vector<std::string> str_vector_t;
typedef std::string str_t;



class Parser {
    Context* context;
    bool exit_flag;
    str_t input_line;
    size_t curr_pos;

    std::map<const str_t, cmd_cstr_t> zero_args_funcs = {
    {"exit", [](Context* ctx) { return new Exit(ctx); }}};

    std::map<const str_t, cmd_cstr_t> one_arg_funcs {
    {"create", [](Context* ctx) { return new CreateFile(ctx); }},
    {"delete", [](Context* ctx) { return new DeleteFile(ctx); }},
    {"edit", [](Context* ctx) { return new EditFile(ctx); }},
    {"read", [](Context* ctx) { return new ReadFile(ctx); }},
    {"crtdir", [](Context* ctx) { return new CreateDir(ctx); }},
    {"deldir", [](Context* ctx) { return new DeleteDir(ctx); }},
    {"rdir", [](Context* ctx) { return new ReadDir(ctx); }},
    {"ldir", [](Context* ctx) { return new LinkDir(ctx); }},
    {"uldir", [](Context* ctx) { return new UnlinkDir(ctx); }}};

    std::map<const str_t, cmd_cstr_t> two_args_funcs{
    {"rename", [](Context* ctx) { return new RenameFile(ctx); }},
    {"move", [](Context* ctx) { return new MoveFile(ctx); }},
    {"rndir", [](Context* ctx) { return new RenameDir(ctx); }}};

    std::map<const str_t, cmd_cstr_t> data_arg_funcs {
    {"write", [](Context* ctx) { return new WriteFile(ctx); }},
    {"append", [](Context* ctx) { return new AppendToFile(ctx); }}};


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
