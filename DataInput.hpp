#pragma once

#include "BaseDataInput.hpp"
#include "DataSource.hpp"


template<typename T>
class DataInput : public BaseDataInput
{
public:


    DataSource(ZigZagObject* parent, std::string_view name)
        : BaseDataSource(parent, name)
    { }


    bool canConnectWith(const BaseDataSource* dataSource) const override
    {
        return dynamic_cast<DataSource<T>*>(dataSource);
    }


    const T* getData() const
    {
        return nullptr;
    }

};
