#include <ZigZag/Object.hpp>
#include <ZigZag/ObjectFactory.hpp>

#include <stdexcept>


using namespace ZigZag;


ObjectFactory* ObjectFactory::instance()
{
    static ObjectFactory objectFactory;
    return &objectFactory;
}



void ObjectFactory::registerType(std::string_view typeName, std::function<Object*()>&& func)
{
    std::string name{ typeName };
    if (!func)
    {
        throw std::runtime_error("Cannot register type without constructor function.");
    }
    if (m_functions.find(name) != m_functions.end())
    {
        throw std::runtime_error("Type name has already been registered.");
    }
    m_functions[name] = std::move(func);
}



Object* ObjectFactory::create(const std::string& typeName) const
{
    auto it = m_functions.find(typeName);
    if (it == m_functions.end())
    {
        throw std::runtime_error("Cannot create object for unknown type name.");
    }
    return it->second();
}
