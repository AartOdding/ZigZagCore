#include "BaseDataInput.hpp"
#include "BaseOperator.hpp"



BaseDataInput::BaseDataInput(ZigZagObject* parent, std::string_view name)
    : ZigZagObject(parent, name),
      ZigZagChild<BaseDataInput, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


BaseDataInput::~BaseDataInput()
{

}


void BaseDataInput::setParent(ZigZagObject* parent)
{
    ZigZagObject::setParent(parent);
    ZigZagChild<BaseDataInput, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}
