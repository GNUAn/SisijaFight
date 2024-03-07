#pragma once
#include <angelscript.h>
#include <string>
#include <vector>
#include <type_traits>

class ScripterSub {
public:
    ScripterSub();
    ~ScripterSub();

    void init();

    // Register a class with the script engine
    void registerClass(const std::string& className, const std::string& typeName);

    // Register a single global object with the script engine
    template<typename T>
    void registerGlobalObject(const std::string& name, T* object, const std::string& typeName);

    // Register an array of objects with the script engine
    template<typename T>
    void registerGlobalArray(const std::string& name, std::vector<T*>& objects, const std::string& typeName);

    template <typename ClassType, typename RetType, typename... Args>
    auto registerClassMethod(const std::string& className, const std::string& declaration, RetType(ClassType::*method)(Args...)) 
        -> typename std::enable_if<(sizeof...(Args) > 0), void>::type {
        std::string fullDeclaration = className + "::" + declaration;
        engine->RegisterObjectMethod(className.c_str(), fullDeclaration.c_str(), asMETHODPR(ClassType, method, (Args...), RetType), asCALL_THISCALL);
    }

    // Für Methoden ohne Parameter und Rückgabetyp void
    template <typename ClassType>
    void registerClassMethod(const std::string& className, const std::string& declaration, void (ClassType::*method)()) {
        std::string fullDeclaration = className + "::" + declaration;
        engine->RegisterObjectMethod(className.c_str(), fullDeclaration.c_str(), asMETHODPR(ClassType, method, (), void), asCALL_THISCALL);
    }

    // Für Methoden ohne Parameter und mit nicht-void Rückgabetyp
    template <typename ClassType, typename RetType>
    auto registerClassMethod(const std::string& className, const std::string& declaration, RetType(ClassType::*method)()) 
        -> typename std::enable_if<!std::is_void<RetType>::value, void>::type {
        std::string fullDeclaration = className + "::" + declaration;
        engine->RegisterObjectMethod(className.c_str(), fullDeclaration.c_str(), asMETHODPR(ClassType, method, (), RetType), asCALL_THISCALL);
    }
protected:
    asIScriptEngine* engine = nullptr;
};

#include "Scripter.Impl.hpp"