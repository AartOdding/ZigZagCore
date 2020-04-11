#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/ParentChildRelationship.hpp>
#include <ZigZag/InputOutputRelationship.hpp>

#include <ZigZag/Variant.hpp>

namespace ZigZag
{


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

};

}
