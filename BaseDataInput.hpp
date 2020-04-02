#pragma once

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"

class BaseOperator;


class BaseDataInput : public ZigZagObject,
                      public ZigZagChild<BaseDataInput, BaseOperator>
{
public:

    BaseDataInput(ZigZagObject* parent = nullptr, std::string_view name = std::string());

    virtual ~BaseDataInput();

    void setParent(ZigZagObject* parent) override;

    virtual bool canConnectWith(const BaseDataSource* dataSource) const = 0;

    bool connect(BaseDataSource* dataSource);
    void disconnect();

    bool isConnected() const;
    bool isConnectedWith(const BaseDataSource* dataSource) const;

    const BaseDataSource* getConnectedDataSource() const;

private:

    BaseDataSource* m_connectedDataSource = nullptr;

};
