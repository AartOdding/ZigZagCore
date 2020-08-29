#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/BaseDataSource.hpp>
#include <ZigZag/BaseDataInput.hpp>
#include <ZigZag/detail/ParentChild.hpp>


namespace ZigZag
{

class BaseOperator : public Object,
                     public detail::Child<BaseOperator, BaseOperator>,
                     public detail::Parent<BaseOperator, BaseOperator>,
                     public detail::Parent<BaseOperator, BaseDataSource>,
                     public detail::Parent<BaseOperator, BaseDataInput>
{
public:

    BaseOperator(Object* parent = nullptr, std::string_view name = std::string_view());

    virtual ~BaseOperator() = default;

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
