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
    m_objectNames.emplace_back(typeName);
    m_objectNamePtrs.clear();

    for (const auto& name : m_objectNames)
    {
        m_objectNamePtrs.emplace_back(name.c_str());
    }

    if (!func)
    {
        throw std::runtime_error("Cannot register type without constructor function.");
    }
    if (m_functions.find(m_objectNames.back()) != m_functions.end())
    {
        throw std::runtime_error("Type name has already been registered.");
    }
    m_functions[m_objectNames.back()] = std::move(func);
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


const std::vector<std::string>& ObjectFactory::getObjectTypeNames() const
{
    return m_objectNames;
}
