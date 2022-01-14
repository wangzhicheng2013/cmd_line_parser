#include "cmd_line_parser.hpp"
int main(int argc, char *argv[]) {
    std::vector<cmd_line_arg>args = { { "apples", "how many apples do you have?"} , { "oranges", "how many oranges do you have?"}, { "help", "show help." } };
    cmd_line_parser my_cmd_line_parser;
    if (my_cmd_line_parser.init(argc, argv, args)) {
        my_cmd_line_parser.parser(args);
        for (auto &arg : args) {
            std::cout << "arg:" << arg.arg_name << " val:" << arg.arg_value << std::endl;
        }
    }

    return 0;
}