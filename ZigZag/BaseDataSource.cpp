#include <ZigZag/BaseDataSource.hpp>
#include <ZigZag/BaseOperator.hpp>



namespace ZigZag
{

BaseDataSource::BaseDataSource(Object* parent, std::string_view name)
    : Object(parent, name),
      ZigZagChild<BaseDataSource, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


BaseDataSource::~BaseDataSource()
{

}


void BaseDataSource::setParent(Object* parent)
{
    Object::setParent(parent);
    ZigZagChild<BaseDataSource, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}

}
