#pragma once

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"
#include "ZigZagInputOutput.hpp"

class BaseOperator;
class BaseDataSource;



class BaseDataInput : public ZigZagObject,
                      public ZigZagChild<BaseDataInput, BaseOperator>,
                      public ZigZagInput<BaseDataInput, BaseDataSource>
{
public:

    BaseDataInput(ZigZagObject* parent = nullptr, std::string_view name = std::string());

    virtual ~BaseDataInput();

    void setParent(ZigZagObject* parent) override;

    //virtual bool canConnectTo(const BaseDataSource* dataSource) const = 0;

};
