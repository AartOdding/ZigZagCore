#pragma once

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"

class BaseOperator;


class BaseDataInput : public ZigZagObject,
                      public ZigZagChild<BaseDataInput, BaseOperator>
{
public:

    BaseDataInput(const std::string& name, ZigZagObject* parent = nullptr);
    BaseDataInput(ZigZagObject* parent = nullptr, const std::string& name = std::string());

    void setParent(ZigZagObject* parent) override;

private:

};
