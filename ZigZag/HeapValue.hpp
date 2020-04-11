#pragma once


namespace ZigZag
{

template<typename T>
class HeapValue
{
public:

    HeapValue()
        : m_value(new T())
    { }

    HeapValue(const T& data)
        : m_value(new T(data))
    { }
    
    HeapValue(T&& data)
        : m_value(new T(std::move(data)))
    { }
    
    HeapValue(const HeapValue& other)
        : m_value(new T(*other.m_value))
    { }
    
    HeapValue(HeapValue&& other)
        : m_value(new T(std::move(*other.m_value)))
    { }

    ~HeapValue()
    {
        delete m_value;
    }

    HeapValue& operator=(const T& data)
    {
        *m_value = data;
        return *this;
    }
    
    HeapValue& operator=(T&& data)
    {
        *m_value = std::move(data);
        return *this;
    }

    HeapValue& operator=(const HeapValue<T>& other)
    {
        *m_value = *other.m_value;
        return *this;
    }
    
    HeapValue& operator=(HeapValue<T>&& other)
    {
        *m_value = std::move(*other.m_value);
        return *this;
    }

    T& value()
    {
        return *m_value;
    }

    const T& value() const
    {
        return *m_value;
    }

private:

    T* m_value = nullptr;

};


}
