#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/detail/ParentChild.hpp>


namespace ZigZag
{

class BaseBehaviour : public Object,
                      public detail::Child<BaseBehaviour, Object>
{
public:

    BaseBehaviour(Object* parent = nullptr, std::string_view name = std::string_view());

    virtual ~BaseBehaviour() = default;

    void setParent(Object* parent) override;

    virtual const char* typeName() const override { return "BaseBehaviour"; }

};

}
