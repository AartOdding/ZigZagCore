#include "BaseOperator.hpp"


BaseOperator::BaseOperator(const std::string& name, ZigZagObject* parent)
    : BaseOperator(parent, name)
{ }


BaseOperator::BaseOperator(ZigZagObject* parent, const std::string& name)
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
