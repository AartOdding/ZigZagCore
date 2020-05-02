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
    ZigZagChild<BaseParameter, Object>::setParent(parent); // no need to cast, already object.
}


void BaseParameter::processPendingChanges()
{
    if (m_hasPendingValue && m_pendingValue != m_value)
    {
        std::swap(m_value, m_pendingValue);
        m_hasPendingValue = false;
        notifyValueChanged();
    }
}


void BaseParameter::notifyValueChanged() const
{
    for (auto* par : getConnectedInputs())
    {
        par->m_pendingValue = m_value;
        par->m_hasPendingValue = true;
    }
}


}
