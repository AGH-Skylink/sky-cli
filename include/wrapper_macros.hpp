#ifndef SKYCLI_WRAPPER_MACROS_H
#define SKYCLI_WRAPPER_MACROS_H

#include "typing.hpp"

#define add_command_to_cli_0(cli_obj, command_name, func) { \
std::vector<skycli::arg_type_t> vec = {}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_1(cli_obj, command_name, func, type1) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_2(cli_obj, command_name, func, type1, type2) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_3(cli_obj, command_name, func, type1, type2, type3) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_4(cli_obj, command_name, func, type1, type2, type3, type4) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_5(cli_obj, command_name, func, type1, type2, type3, type4, type5) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name()), skycli::deduce_type(typeid(type5).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3), std::any_cast<type5>(args->_4)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli_6(cli_obj, command_name, func, type1, type2, type3, type4, type5, type6) { \
std::vector<skycli::arg_type_t> vec = {skycli::deduce_type(typeid(type1).name()), skycli::deduce_type(typeid(type2).name()), skycli::deduce_type(typeid(type3).name()), skycli::deduce_type(typeid(type4).name()), skycli::deduce_type(typeid(type5).name()), skycli::deduce_type(typeid(type6).name())}; \
std::function<void(skycli::BaseArgs *)> func##_wrapper = [](skycli::BaseArgs *args) { \
    func(std::any_cast<type1>(args->_0), std::any_cast<type2>(args->_1), std::any_cast<type3>(args->_2), std::any_cast<type4>(args->_3), std::any_cast<type5>(args->_4), std::any_cast<type6>(args->_5)); \
}; \
cli_obj.add_command(#command_name, func##_wrapper, vec); \
}

#define add_command_to_cli(cli_obj, command_name, func, number_of_args, ...) \
add_command_to_cli_##number_of_args (cli_obj, command_name, func, __VA_ARGS__)

#endif //SKYCLI_WRAPPER_MACROS_H