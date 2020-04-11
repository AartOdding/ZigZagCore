#include <ZigZag/BaseParameter.hpp>
#include <ZigZag/BaseOperator.hpp>


namespace ZigZag
{

BaseParameter::BaseParameter(Object* parent, std::string_view name)
    : Object(parent, name),
      ZigZagChild<BaseParameter, Object>(parent),
      ZigZagChild<BaseParameter, BaseParameter>(dynamic_cast<BaseParameter*>(parent))
{
    
}


BaseParameter::~BaseParameter()
{

}


void BaseParameter::setParent(Object* parent)
{
    Object::setParent(parent);
    ZigZagChild<BaseParameter, Object>::setParent(parent); // no need to cast, already object.
    ZigZagChild<BaseParameter, BaseParameter>::setParent(dynamic_cast<BaseParameter*>(parent));
}


const std::vector<BaseParameter*>& BaseParameter::getChildParameters() const
{
    return ZigZagParent<BaseParameter, BaseParameter>::getChildren();
}


}
