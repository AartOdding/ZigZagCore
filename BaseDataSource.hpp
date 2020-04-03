#pragma once

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"
#include "ZigZagInputOutput.hpp"

class BaseOperator;
class BaseDataInput;



class BaseDataSource : public ZigZagObject,
                       public ZigZagChild<BaseDataSource, BaseOperator>,
                       public ZigZagOutput<BaseDataSource, BaseDataInput>
{
public:

    BaseDataSource(ZigZagObject* parent = nullptr, std::string_view name = std::string());

    ~BaseDataSource();

    void setParent(ZigZagObject* parent) override;

};
