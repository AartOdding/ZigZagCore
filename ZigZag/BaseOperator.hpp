#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/ParentChildRelationship.hpp>
#include <ZigZag/BaseDataSource.hpp>
#include <ZigZag/BaseDataInput.hpp>


namespace ZigZag
{

class BaseOperator : public Object,
                     public ZigZagChild<BaseOperator, BaseOperator>,
                     public ZigZagParent<BaseOperator, BaseOperator>,
                     public ZigZagParent<BaseOperator, BaseDataSource>,
                     public ZigZagParent<BaseOperator, BaseDataInput>
{
public:

    BaseOperator(Object* parent = nullptr, std::string_view name = std::string());

    //virtual void execute() = 0;

    virtual void onFrameStart() { }
    virtual void onFrameEnd() { }

    virtual void setParent(Object* parent) override;

    const std::vector<BaseOperator*>& getChildOperators() const;
    const std::vector<BaseDataSource*>& getDataSources() const;
    const std::vector<BaseDataInput*>& getDataInputs() const;
    
    virtual const char* typeName() const override { return "BaseOperator"; }

private:


};

}
