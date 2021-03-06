#include <ZigZag/BaseDataInput.hpp>
#include <ZigZag/BaseOperator.hpp>


namespace ZigZag
{

BaseDataInput::BaseDataInput(Object* parent, std::string_view name)
    : Object(parent, name),
      Child<BaseDataInput, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


void BaseDataInput::setParent(Object* parent)
{
    Object::setParent(parent);
    Child<BaseDataInput, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}

}
