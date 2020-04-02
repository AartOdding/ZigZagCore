#include "BaseOperator.hpp"



BaseOperator::BaseOperator(ZigZagObject* parent, std::string_view name)
    : ZigZagObject(parent, name)
{ }


const std::vector<BaseDataSource*>& BaseOperator::getDataSources() const
{
    return ZigZagParent<BaseOperator, BaseDataSource>::getChildren();
}


const std::vector<BaseDataInput*>& BaseOperator::getDataInputs() const
{
    return ZigZagParent<BaseOperator, BaseDataInput>::getChildren();
}
