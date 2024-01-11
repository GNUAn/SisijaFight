#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include "Scripting.hpp"
#include "../globals.hpp"

void MessageCallback(const char* message){
    device->getLogger()->log(message,"AS-Scripting Engine", ELL_ERROR);
}

void ScripterSub::init() {
    engine = asCreateScriptEngine();
    int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
    RegisterStdString(engine);
}

/// @brief Register a Function to Angelscript
/// @tparam ...Args The Function Arguments template
/// @param callb callback function
/// @param name name of the function (e.g. void print(string data))
/// @param type Type: Class member, namespace member or global function
/// @param cls Optional: Class name
/// @param nmspc Optional: Namespace name
template <typename... Args>
void ScripterSub::registerFunction(std::function<void(Args...)> callb, std::string name, RegistryType type, std::string cls, std::string nmspc){
    switch(type){
    case SSE_GLOBAL:
        break;
    }
}