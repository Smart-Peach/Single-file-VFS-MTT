#pragma once 

#include "includes.hpp"
#include "Lexer.hpp"
#include "../../includes/types.hpp" 


//TODO: add context as arg / or impl some derived classes of ctx
typedef std::function<Command*()> cmd_cstr_t;
typedef std::vector<str_t> str_vector_t;


class Parser {
    Lexer lexer;
    Context* context;

    bool exit_flag;
    str_t input_line;
    size_t curr_pos;

    std::map<const str_t, cmd_cstr_t> zero_args_funcs = {
    {"exit", []() { return new Exit(); }},
    {"pwd", []() { return new Pwd(); }}, 
    {"help", []() { return new Help(); }},
    {"ls", []() { return new Ls();}}};

    std::map<const str_t, cmd_cstr_t> one_arg_funcs {
    {"create", []() { return new CreateFile(); }},
    {"cd", []() { return new ChangeDir(); }},
    {"delete", []() { return new DeleteFile(); }},
    {"edit", []() { return new EditFile(); }},
    {"read", []() { return new ReadFile(); }},
    {"crtdir", []() { return new CreateDir(); }},
    {"deldir", []() { return new DeleteDir(); }},
    {"rdir", []() { return new ReadDir(); }}};

    std::map<const str_t, cmd_cstr_t> two_args_funcs{
    {"rename", []() { return new RenameFile(); }},
    {"move", []() { return new MoveFile(); }},
    {"rndir", []() { return new RenameDir(); }}};

    std::map<const str_t, cmd_cstr_t> data_arg_funcs {
    {"write", []() { return new WriteFile(); }},
    {"append", []() { return new AppendToFile(); }}};


public:
    Parser(Context* context, str_t input_line):
                            lexer(Lexer(input_line)),
                            context(context),
                            input_line(input_line),
                            curr_pos(-1),
                            exit_flag(false) { }
    ~Parser() = default;

    Command* next_command();

private:
    Command* parse(str_t token);
};
