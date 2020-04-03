#pragma once

#include "ZigZag/Object.hpp"
#include "ZigZag/ZigZagParentChild.hpp"
#include "ZigZag/BaseDataSource.hpp"
#include "ZigZag/BaseDataInput.hpp"


namespace ZigZag
{

class BaseOperator : public Object,
                     public ZigZagParent<BaseOperator, BaseDataSource>,
                     public ZigZagParent<BaseOperator, BaseDataInput>
{
public:

    BaseOperator(Object* parent = nullptr, std::string_view name = std::string());

    //virtual void execute() = 0;

    virtual void onFrameStart() { }
    virtual void onFrameEnd() { }

    const std::vector<BaseDataSource*>& getDataSources() const;
    const std::vector<BaseDataInput*>& getDataInputs() const;

private:


};

}
