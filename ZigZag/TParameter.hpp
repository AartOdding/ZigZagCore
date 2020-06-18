#pragma once

#include <ZigZag/BaseParameter.hpp>


template<typename T, const char* NAME>
class TParameter : public ZigZag::BaseParameter
{
public:

    TParameter(Object* parent = nullptr, std::string_view name = std::string())
        : BaseParameter(parent, name),
          m_value(T())
    { }

    const T& value() const
    {
        return m_value;
    }

    template<typename X>
    void set(X&& newValue)
    {
        if (m_value != newValue)
        {
            m_value = newValue;
            notifyNewValue(m_value);
        }
    }

    template<typename X>
    TParameter& operator=(X&& newValue)
    {
        if (m_value != newValue)
        {
            m_value = newValue;
            notifyNewValue(m_value);
        }
        return *this;
    }
    
    virtual void extractNewValue(const std::any& newValue) override
    {
        try
        {
            set(std::any_cast<T>(newValue));
        }
        catch(const std::bad_any_cast& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    virtual const char* typeName() const override
    {
        return NAME;
    }

private:

    T m_value;

};
