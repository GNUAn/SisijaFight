#pragma once

template<typename T>
void ScripterSub::registerGlobalObject(const std::string& name, T* object, const std::string& typeName) {
    std::string declaration = typeName + "@ " + name;
    engine->RegisterGlobalProperty(declaration.c_str(), object);
}

template<typename T>
void ScripterSub::registerGlobalArray(const std::string& name, std::vector<T*>& objects, const std::string& typeName) {
    std::string arrayTypeName = "array<" + typeName + "@>";
    engine->RegisterGlobalProperty(arrayTypeName.c_str(), &objects);
}