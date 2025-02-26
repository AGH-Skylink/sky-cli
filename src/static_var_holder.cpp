#include "../include/static_var_holder.hpp"

namespace skycli {

StaticVarBase *StaticVarHolder::get_ptr(std::string var_name) {
    if (this->variables.find(var_name) != this->variables.end()) {
        return this->variables[var_name].get();
    }
    else {
        return this->dummy.get();
    }
}

StaticVarBase *StaticVarHolder::attempt_var_retrieval(std::string var_name, std::ostream &stream) {
    StaticVarBase *var = this->get_ptr(var_name);

    if (var == this->dummy.get()) {
        stream << "Warning: Static variable of that name was not found, returning a dummy" << std::endl;
    }

    return var;
}

} // namespace skycli