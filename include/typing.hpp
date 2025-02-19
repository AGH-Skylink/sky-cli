#ifndef SKYCLI_TYPING_H
#define SKYCLI_TYPING_H

#include <array>
#include <string>

namespace skycli {

enum arg_type_t {
    BOOL = 0,
    INT = 1,
    FLOAT = 2,
    DOUBLE = 3,
    CHAR = 4,
    STRING = 5
};

class TypingUtil {
private:
    const std::array<std::string, 6> type_names = {"bool", "int", "float", "double", "char", "string"};

public:
    /** @brief Returns the type 
    *
    * Returns an arg_type_t value, that matches the type given 
    * by the type_name.
    * 
    * @param[in] type_name 
    */
    arg_type_t deduce_type(const char *type_name);

    std::string get_type_string(arg_type_t type);
};

} // namespace skycli

#endif //SKYCLI_TYPING_H