#include "BaseDataSource.hpp"
#include "BaseOperator.hpp"



BaseDataSource::BaseDataSource(ZigZagObject* parent, std::string_view name)
    : ZigZagObject(parent, name),
      ZigZagChild<BaseDataSource, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


BaseDataSource::~BaseDataSource()
{

}


void BaseDataSource::setParent(ZigZagObject* parent)
{
    ZigZagObject::setParent(parent);
    ZigZagChild<BaseDataSource, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}
