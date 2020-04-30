#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/ParentChildRelationship.hpp>
#include <ZigZag/InputOutputRelationship.hpp>


namespace ZigZag
{

class Variant
{
public: 
    std::string dummy;  
};

class BaseParameter : public Object,
                      public ZigZagChild<BaseParameter, Object>,
                      public ZigZagChild<BaseParameter, BaseParameter>,
                      public ZigZagParent<BaseParameter, BaseParameter>,
                      public ZigZagInput<BaseParameter, BaseParameter>,
                      public ZigZagOutput<BaseParameter, BaseParameter>
{
public:

    BaseParameter(Object* parent = nullptr, std::string_view name = std::string());

    virtual ~BaseParameter();

    void setParent(Object* parent) override;

    const std::vector<BaseParameter*>& getChildParameters() const;

    virtual void process() = 0;

    virtual void consume(const Variant& var) = 0;

    // will supply the changed value to all the consumers.
    // This means all parameters connected to this as an input will get 
    // consume called with var as argument.
    void supply(const Variant& var) const;

};

}
