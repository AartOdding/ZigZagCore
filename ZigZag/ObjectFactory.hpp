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

    // ownership is given to caller.
    Object* create(const std::string& typeName) const;

private:

    ObjectFactory() = default;

    std::unordered_map<std::string, std::function<Object*()>> m_functions;

};


}
