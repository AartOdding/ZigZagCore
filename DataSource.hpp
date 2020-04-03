#pragma once

#include "ZigZag/BaseDataSource.hpp"


template<typename T>
class DataSource : public ZigZag::BaseDataSource
{
public:


    DataSource(ZigZag::Object* parent, std::string_view name, T* data)
        : ZigZag::BaseDataSource(parent, name),
          m_data(data)
    { }


    void setData(T* data)
    {
        m_data = data;
    }


    T* getData()
    {
        return m_data;
    }


private:

    T* m_data;

};
