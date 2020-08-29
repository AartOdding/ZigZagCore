#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/ParentChildRelationship.hpp>
#include <ZigZag/InputOutputRelationship.hpp>



namespace ZigZag
{

class BaseOperator;
class BaseDataInput;


class BaseDataSource : public Object,
                       public ZigZagChild<BaseDataSource, BaseOperator>,
                       public ZigZagOutput<BaseDataSource, BaseDataInput>
{
public:

    BaseDataSource(Object* parent = nullptr, std::string_view name = std::string_view());

    virtual ~BaseDataSource() = default;

    void setParent(Object* parent) override;

    virtual const char* typeName() const override { return "BaseDataSource"; }

};

}
