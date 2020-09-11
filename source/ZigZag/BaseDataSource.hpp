#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/detail/ParentChild.hpp>
#include <ZigZag/detail/InputOutput.hpp>



namespace ZigZag
{

class BaseOperator;
class BaseDataInput;


class BaseDataSource : public Object,
                       public detail::Child<BaseDataSource, BaseOperator>,
                       public detail::Output<BaseDataSource, BaseDataInput>
{
public:

    BaseDataSource(Object* parent = nullptr, std::string_view name = std::string_view());

    virtual ~BaseDataSource() = default;

    void setParent(Object* parent) override;

    virtual const char* typeName() const override { return "BaseDataSource"; }

};

}
