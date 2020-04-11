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

    BaseDataSource(Object* parent = nullptr, std::string_view name = std::string());

    ~BaseDataSource();

    void setParent(Object* parent) override;

};

}
