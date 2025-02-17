#ifndef SKYCLI_TYPING_H
#define SKYCLI_TYPING_H

namespace skycli {

enum arg_type_t {
    BOOL = 0,
    INT = 1,
    FLOAT = 2,
    DOUBLE = 3,
    CHAR = 4,
    STRING = 5
};

/** @brief Returns the type 
*
* Returns an arg_type_t value, that matches the type given 
* by the type_name.
* 
* @param[in] type_name 
*/
arg_type_t deduce_type(const char *type_name);

} // namespace skycli

#endif //SKYCLI_TYPING_H