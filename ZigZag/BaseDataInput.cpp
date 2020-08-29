#include <ZigZag/BaseDataInput.hpp>
#include <ZigZag/BaseOperator.hpp>


namespace ZigZag
{

BaseDataInput::BaseDataInput(Object* parent, std::string_view name)
    : Object(parent, name),
      ZigZagChild<BaseDataInput, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


void BaseDataInput::setParent(Object* parent)
{
    Object::setParent(parent);
    ZigZagChild<BaseDataInput, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}

}
