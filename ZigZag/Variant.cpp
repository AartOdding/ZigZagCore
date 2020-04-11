#include <ZigZag/Variant.hpp>



namespace ZigZag
{

bool Variant::isNull() const
{
    return !std::holds_alternative<std::monostate>(m_storage);
}


void Variant::clear()
{
    m_storage = std::monostate();
}


VariantType Variant::getType() const
{
    return static_cast<VariantType>(m_storage.index());
}


bool Variant::hasType(VariantType type) const
{
    return type == getType();
}

}
