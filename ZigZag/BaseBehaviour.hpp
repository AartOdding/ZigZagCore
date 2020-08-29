#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/ParentChildRelationship.hpp>


namespace ZigZag
{

class BaseBehaviour : public Object,
                      public ZigZagChild<BaseBehaviour, Object>
{
public:

    BaseBehaviour(Object* parent = nullptr, std::string_view name = std::string_view());

    virtual ~BaseBehaviour() = default;

    void setParent(Object* parent) override;

    virtual const char* typeName() const override { return "BaseBehaviour"; }

};

}
