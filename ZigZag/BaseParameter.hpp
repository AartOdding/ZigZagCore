#pragma once

#include <any>

#include <ZigZag/Object.hpp>
#include <ZigZag/ParentChildRelationship.hpp>
#include <ZigZag/InputOutputRelationship.hpp>


namespace ZigZag
{


class BaseParameter : public Object,
                      public ZigZagChild<BaseParameter, Object>,
                      public ZigZagInput<BaseParameter, BaseParameter>,
                      public ZigZagOutput<BaseParameter, BaseParameter>
{
public:

    BaseParameter(Object* parent = nullptr, std::string_view name = std::string_view());

    virtual ~BaseParameter() = default;

    void setParent(Object* parent) override;

    virtual const char* typeName() const override { return "BaseParameter"; }

    void process();

protected:

    void notifyNewValue(const std::any& newValue) const;

    virtual void extractNewValue(const std::any& newValue) = 0;


private:

    std::any m_pendingValue;

    bool m_hasPendingValue = false;


};

}
