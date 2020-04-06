#include "ZigZag/BaseOperator.hpp"



namespace ZigZag
{

BaseOperator::BaseOperator(Object* parent, std::string_view name)
    : Object(parent, name),
      ZigZagChild<BaseOperator, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{

}


void BaseOperator::setParent(Object* parent)
{
    Object::setParent(parent);
    ZigZagChild<BaseOperator, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}


const std::vector<BaseOperator*>& BaseOperator::getChildOperators() const
{
    return ZigZagParent<BaseOperator, BaseOperator>::getChildren();
}


const std::vector<BaseDataSource*>& BaseOperator::getDataSources() const
{
    return ZigZagParent<BaseOperator, BaseDataSource>::getChildren();
}


const std::vector<BaseDataInput*>& BaseOperator::getDataInputs() const
{
    return ZigZagParent<BaseOperator, BaseDataInput>::getChildren();
}

}
