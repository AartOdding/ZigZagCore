#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>



namespace ZigZag
{

class Object;


class ObjectFactory
{
public:

    ObjectFactory(const ObjectFactory&) = delete;
    ObjectFactory(ObjectFactory&&) = delete;

    static ObjectFactory* instance();

    void registerType(std::string_view typeName, std::function<Object*()>&& func);

    // Ownership is given to caller.
    Object* create(const std::string& typeName) const;

    const std::vector<std::string>& getObjectTypeNames() const;


private:

    ObjectFactory() = default;

    std::unordered_map<std::string, std::function<Object*()>> m_functions;
    std::vector<std::string> m_objectNames;
    std::vector<const char*> m_objectNamePtrs;

};


}
