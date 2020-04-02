#pragma once

#include "BaseDataSource.hpp"


template<typename T>
class DataSource : public BaseDataSource
{
public:


    DataSource(ZigZagObject* parent, std::string_view, T* data)
        : BaseDataSource(parent, name),
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
