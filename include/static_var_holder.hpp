#ifndef SKYCLI_VAR_HOLDER
#define SKYCLI_VAR_HOLDER

#include "typing_util.hpp"

#include <map>
#include <string>
#include <memory>

namespace skycli {

class StaticVarBase {};

template <typename T>
class StaticVar : public StaticVarBase {
private:
    T value;

public:
    StaticVar() = default;

    T &get() {
        return value;
    }
};

class StaticVarHolder {
private:
    std::map<std::string, std::unique_ptr<StaticVarBase>> variables;

public:
    template <typename T>
    void add_new_var(std::string var_name) {
        variables[var_name] = std::make_unique<StaticVar<T>>();
    }

    StaticVarBase *get_ptr(std::string var_name) {
        return variables[var_name].get();
    }
};

} // namespace skycli

#endif //SKYCLI_VAR_HOLDER