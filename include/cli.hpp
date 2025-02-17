#ifndef SKYCLI_CLI_H
#define SKYCLI_CLI_H

#include "command.hpp"
#include "parser.hpp"

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>

namespace skycli {

class CLI {
private:
    std::map<std::string, std::unique_ptr<Command>> commands;
    const std::string prompt;
    std::shared_ptr<Parser> parser;

    bool handle_cmd_response(CmdResponse response);

public:
    CLI() : prompt{"> "} {
        this->parser = std::make_shared<Parser>();
    }

    CLI(const char &delim) : prompt{"> "} {
        this->parser = std::make_shared<Parser>(delim);
    }

    CLI(const std::string &prompt_text) : prompt{prompt_text} {
        this->parser = std::make_shared<Parser>();
    }

    CLI(const std::string &prompt_text, const char &delim) : prompt{prompt_text} {
        this->parser = std::make_shared<Parser>(delim);
    }

    void add_command(std::string command_name, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec);

    void run_loop();
};

} // namespace skycli

#endif //SKYCLI_CLI_H