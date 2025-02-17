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

    /** @brief Handle a CmdResponse during runtime
    *
    * Returns true if the response was succesful, false otherwise
    * 
    * @param[in] response the response to handle
    */
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

    /** @brief Adds a new command to the CLI
    *
    * Maps a function to the given command name.
    * Created Command object is supplied with the type vector.
    * 
    * @param[in] command_name the name which will be mapped to the command
    * @param[in] func function to be called by the command
    * @param[in] type_vec vector of function arguments' types
    */
    void add_command(std::string command_name, std::function<void(BaseArgs *)> func, std::vector<arg_type_t> type_vec);

    /** @brief Run CLI
    *
    * Runs the main loop of the CLI
    * 
    * @param[in] void
    */
    void run_loop();
};

} // namespace skycli

#endif //SKYCLI_CLI_H