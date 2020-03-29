#include "BaseDataInput.hpp"
#include "BaseOperator.hpp"


BaseDataInput::BaseDataInput(const std::string& name, ZigZagObject* parent)
    : BaseDataInput(parent, name)
{ }


BaseDataInput::BaseDataInput(ZigZagObject* parent, const std::string& name)
    : ZigZagObject(parent, name),
      ZigZagChild<BaseDataInput, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


void BaseDataInput::setParent(ZigZagObject* parent)
{
    ZigZagObject::setParent(parent);
    ZigZagChild<BaseDataInput, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}
