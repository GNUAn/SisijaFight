#include <angelscript.h>
#include <string>
#include <functional>

/// @brief Registry Type for Script Engine
enum RegistryType{
    SSE_GLOBAL, SSE_CLASS, SSE_NAMESPACE
};

/// @brief Simple Scripter Subsystem
class ScripterSub {
    public:
    void init();
    template <typename... Args>
    void registerFunction(std::function<void(Args...)> callb, std::string name, RegistryType type, std::string cls="", std::string nmspc="");
    protected:
    asIScriptEngine* engine;
}