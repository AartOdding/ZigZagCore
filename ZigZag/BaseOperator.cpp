#include "ZigZag/BaseOperator.hpp"



namespace ZigZag
{

BaseOperator::BaseOperator(Object* parent, std::string_view name)
    : Object(parent, name)
{ }


const std::vector<BaseDataSource*>& BaseOperator::getDataSources() const
{
    return ZigZagParent<BaseOperator, BaseDataSource>::getChildren();
}


const std::vector<BaseDataInput*>& BaseOperator::getDataInputs() const
{
    return ZigZagParent<BaseOperator, BaseDataInput>::getChildren();
}

}
