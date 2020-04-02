#pragma once

#include <vector>

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"

class BaseOperator;
class BaseDataInput;


class BaseDataSource : public ZigZagObject,
                       public ZigZagChild<BaseDataSource, BaseOperator>
{
public:

    BaseDataSource(ZigZagObject* parent = nullptr, std::string_view name = std::string());

    ~BaseDataSource();

    void setParent(ZigZagObject* parent) override;

    bool connect(BaseDataInput* dataInput);
    void disconnect();

    bool isConnected() const;
    bool isConnectedWith(BaseDataInput* dataInput) const;

    const BaseDataSource* getConnectedDataInputs() const;

private:

    friend class BaseDataSource;

    std::vector<BaseDataSource*> m_connectedDataSources;

};
