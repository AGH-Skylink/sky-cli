#ifndef SKYCLI_STATIC_VAR_MACROS_H
#define SKYCLI_STATIC_VAR_MACROS_H

#define REGISTER_VAR(name, type) \
typedef type name##typeobfuscate

#define ADD_VAR(cli_obj, name) \
cli_obj.add_static_var<name##typeobfuscate>(#name)

#define STATIC_VARS() \
skycli::StaticVarHolder *STATICVARSOBFUSCATE

#define GET_VAR_H(holder_name, name) \
(static_cast<skycli::StaticVar<name##typeobfuscate> *>(holder_name->get_ptr(#name)))->get()

#define GET_VAR(name) \
(static_cast<skycli::StaticVar<name##typeobfuscate> *>(STATICVARSOBFUSCATE->get_ptr(#name)))->get()

#endif