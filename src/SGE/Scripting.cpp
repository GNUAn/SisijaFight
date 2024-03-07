#include "Scripting.hpp"
#include <stdexcept>

ScripterSub::ScripterSub() : engine(nullptr) {

}

ScripterSub::~ScripterSub() {
    if (engine) {
        engine->ShutDownAndRelease();
    }
}

#include <scriptstdstring/scriptstdstring.h>
#include <scriptarray/scriptarray.h>
#include <assert.h>

void ScripterSub::init() {
    engine = asCreateScriptEngine();
    if (engine == nullptr) {
        throw std::runtime_error("Failed to create script engine.");
    }

    RegisterStdString(engine);
    RegisterScriptArray(engine, false);
}

void ScripterSub::registerClass(const std::string& className, const std::string& typeName) {
    engine->RegisterObjectType(className.c_str(), 0, asOBJ_REF | asOBJ_NOCOUNT);
}