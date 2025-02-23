#include "cli.hpp"

#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>

namespace skycli {

void CLI::print_help(std::ostream &stream) {
    stream << "AVAILABLE COMMANDS:" << std::endl;

    for (auto msg : help_messages) {
        msg.print_message(stream);
    }

    stream << "help/HELP - argument #: 0" << std::endl;
    stream << "    " << "Lists all available commands" << std::endl;
    stream << "--------------------" << std::endl; 

    stream << "exit/EXIT - argument #: 0" << std::endl;
    stream << "    " << "Exits the CLI" << std::endl;
    stream << "--------------------" << std::endl; 
}

bool CLI::handle_cmd_response(CmdResponse response) {
    TypingUtil util;

    switch(response.error_code) {
        case NO_ERROR:
            return true;
        case INSUFFICIENT_ARGS:
            std::cout << "Warning: Insufficient number of arguments. Expected: " << response.arg_count << ", received: " << response.error_arg_num << std::endl;
            return false;
        case WRONG_TYPE_ARG:
            std::cout << "Warning: Wrong type of argument #" << response.error_arg_num + 1 << ". Argument type should be: " << util.get_type_string(response.arg_type) << std::endl;
            return false;
        default:
            throw std::runtime_error("Unknown CmdResponse error code.");
    }
}

void CLI::add_command(std::string command_name, std::string description, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec) {
    this->commands[command_name] = std::make_unique<Command>(func, type_vec, this->parser, this->static_vars);
    HelpMessage msg{command_name, description, type_vec};
    this->help_messages.push_back(msg);
}

void CLI::run_loop() {
    char *temp;
    std::string curr_line;
    std::optional<std::string> cmd_token;
    CmdResponse response;

    while (true) {
        temp = readline(this->prompt.c_str());
        curr_line = temp;
        free(temp);

        this->parser->load_line(curr_line);
        cmd_token = this->parser->get_next_token(STRING);

        if (!cmd_token.value().empty()) {
            if (cmd_token.value() == "exit" || cmd_token.value() == "EXIT") {
                break;
            }
            else if (cmd_token.value() == "help" || cmd_token.value() == "HELP") {
                this->print_help(std::cout);
                continue;
            }

            if (this->commands.find(cmd_token.value()) != this->commands.end()) {
                response = this->commands[cmd_token.value()]->load_arguments();

                if (handle_cmd_response(response)) {
                    this->commands[cmd_token.value()]->execute();
                }
            }
            else {
                std::cout << "Unknown command. Maybe try using \'help\'?" << std::endl;
            }
        }
        
        add_history(curr_line.c_str());
    }
}

} // namespace skycli