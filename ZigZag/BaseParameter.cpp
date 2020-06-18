#include <ZigZag/BaseParameter.hpp>
#include <ZigZag/BaseOperator.hpp>


namespace ZigZag
{

BaseParameter::BaseParameter(Object* parent, std::string_view name)
    : Object(parent, name),
      ZigZagChild<BaseParameter, Object>(parent)
{
    
}


BaseParameter::~BaseParameter()
{

}


void BaseParameter::setParent(Object* parent)
{
    Object::setParent(parent);
    ZigZagChild<BaseParameter, Object>::setParent(parent); // no need to cast, already object type.
}


void BaseParameter::process()
{
    if (m_hasPendingValue)
    {
        extractNewValue(m_pendingValue);
        m_hasPendingValue = false;
    }
}


void BaseParameter::notifyNewValue(const std::any& newValue) const
{
    for (auto* par : getConnectedInputs())
    {
        par->m_pendingValue = newValue;
        par->m_hasPendingValue = true;
    }
}


}
