#pragma once

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"

class BaseOperator;


class BaseDataSource : public ZigZagObject,
                       public ZigZagChild<BaseDataSource, BaseOperator>
{
public:

    BaseDataSource(const std::string& name, ZigZagObject* parent = nullptr);
    BaseDataSource(ZigZagObject* parent = nullptr, const std::string& name = std::string());

    void setParent(ZigZagObject* parent) override;

private:

};

