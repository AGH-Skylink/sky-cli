#ifndef SKYCLI_COMMAND_H
#define SKYCLI_COMMAND_H

#include "typing.hpp"
#include "parser.hpp"

#include <functional>
#include <any>
#include <memory>

namespace skycli 
{

struct BaseArgs {
    std::any _0;
    std::any _1;
    std::any _2;
    std::any _3;
    std::any _4;
    std::any _5;
};

class Command {
private:
    std::function<void(BaseArgs *)> func;
    std::unique_ptr<BaseArgs> args;
    size_t arg_count;
    std::vector<arg_type_t> arg_types;
    std::shared_ptr<Parser> parser;

public:
    Command() {
        this->args = std::make_unique<BaseArgs>();
        this->arg_count = 0;
    }

    Command(std::function<void(BaseArgs *)> f, std::vector<arg_type_t> v, std::shared_ptr<Parser> parser_ptr) {
        this->func = f;
        this->args = std::make_unique<BaseArgs>();
        this->arg_types = v;
        this->arg_count = v.size();
        this->parser = parser_ptr;
    }

    Command &operator=(const Command& other) {
        this->func = other.func;
        this->arg_count = other.arg_count;
        this->arg_types = other.arg_types;
        this->parser = other.parser;

        for (size_t i = 0; i < this->arg_count; i++) {
            this->get_arg(i) = other.get_arg(i);
        }

        return *this;
    }

    std::any &get_arg(const int i) const;
    
    void execute();
};

} // namespace skycli

#endif //SKYCLI_COMMAND_H