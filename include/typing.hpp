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

arg_type_t deduce_type(const char *type_name);

}

#endif //SKYCLI_TYPING_H