#pragma once

#include "ZigZag/Object.hpp"
#include "ZigZag/ParentChildRelationship.hpp"
#include "ZigZag/InputOutputRelationship.hpp"


namespace ZigZag
{

class BaseOperator;
class BaseDataSource;


class BaseDataInput : public Object,
                      public ZigZagChild<BaseDataInput, BaseOperator>,
                      public ZigZagInput<BaseDataInput, BaseDataSource>
{
public:

    BaseDataInput(Object* parent = nullptr, std::string_view name = std::string());

    virtual ~BaseDataInput();

    void setParent(Object* parent) override;

    //virtual bool canConnectTo(const BaseDataSource* dataSource) const = 0;

};

}
