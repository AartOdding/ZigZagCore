#include <ZigZag/BaseDataSource.hpp>
#include <ZigZag/BaseOperator.hpp>



namespace ZigZag
{

BaseDataSource::BaseDataSource(Object* parent, std::string_view name)
    : Object(parent, name),
      Child<BaseDataSource, BaseOperator>(dynamic_cast<BaseOperator*>(parent))
{
    
}


void BaseDataSource::setParent(Object* parent)
{
    Object::setParent(parent);
    Child<BaseDataSource, BaseOperator>::setParent(dynamic_cast<BaseOperator*>(parent));
}

}
