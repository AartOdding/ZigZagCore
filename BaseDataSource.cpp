#include "BaseDataSource.hpp"
#include "BaseOperator.hpp"


BaseDataSource::BaseDataSource(const std::string& name, ZigZagObject* parent)
    : BaseDataSource(parent, name)
{ }


BaseDataSource::BaseDataSource(ZigZagObject* parent, const std::string& name)
    : ZigZagObject(parent, name),
      ZigZagChild<BaseDataSource, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


void BaseDataSource::setParent(ZigZagObject* parent)
{
    ZigZagObject::setParent(parent);
    ZigZagChild<BaseDataSource, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}
