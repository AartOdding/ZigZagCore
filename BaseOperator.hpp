#pragma once

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"
#include "BaseDataSource.hpp"
#include "BaseDataInput.hpp"


class BaseOperator : public ZigZagObject,
                     public ZigZagParent<BaseOperator, BaseDataSource>,
                     public ZigZagParent<BaseOperator, BaseDataInput>
{
public:

    BaseOperator(ZigZagObject* parent = nullptr, std::string_view name = std::string());

    //virtual void execute() = 0;

    virtual void onFrameStart() { }
    virtual void onFrameEnd() { }

    const std::vector<BaseDataSource*>& getDataSources() const;
    const std::vector<BaseDataInput*>& getDataInputs() const;

private:


};
