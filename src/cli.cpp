#include "cli.hpp"

#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>

namespace skycli {

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

void CLI::add_command(std::string command_name, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec) {
    this->commands[command_name] = std::make_unique<Command>(func, type_vec, this->parser, this->static_vars);
}

void CLI::run_loop() {
    std::string curr_line;
    std::optional<std::string> cmd_token;
    CmdResponse response;

    while (true) {
        curr_line = readline(this->prompt.c_str());
        
        this->parser->load_line(curr_line);
        cmd_token = this->parser->get_next_token(STRING);

        if (!cmd_token.value().empty()) {
            if (cmd_token.value() == "exit" || cmd_token.value() == "EXIT") {
                break;
            }

            if (this->commands.find(cmd_token.value()) != this->commands.end()) {
                response = this->commands[cmd_token.value()]->load_arguments();

                if (handle_cmd_response(response)) {
                    this->commands[cmd_token.value()]->execute();
                }
            }
        }
        
        add_history(curr_line.c_str());
    }
}

} // namespace skycli