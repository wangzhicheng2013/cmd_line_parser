#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
namespace opt = boost::program_options;
struct cmd_line_arg {
    const char *arg_name;
    const char *arg_tip;
    std::string arg_value;
};
class cmd_line_parser {
public:
    bool init(int argc, char *argv[], const std::vector<cmd_line_arg>&args) {
        for (auto &arg : args) {
            desc_.add_options()(arg.arg_name, opt::value<std::string>(), arg.arg_tip);
        }
        try {
            opt::store(opt::parse_command_line(argc, argv, desc_), vm_);
            opt::notify(vm_);
        }
        catch (std::exception &e) {
            std::cerr << "init exception:" << e.what() << std::endl;
            return false;
        }
        return true;
    }
    void parser(std::vector<cmd_line_arg>&args) {
        for (auto &arg : args) {
            if (vm_.count(arg.arg_name) && arg.arg_name != "help")  {
                arg.arg_value = vm_[arg.arg_name].as<std::string>();
            }
        }
    }
private:
    std::vector<cmd_line_arg>args_;
    opt::options_description desc_;
    opt::variables_map vm_;
};