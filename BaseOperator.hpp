#pragma once

#include "ZigZagObject.hpp"
#include "ZigZagParentChild.hpp"
#include "BaseDataSource.hpp"
#include "BaseDataInput.hpp"


class BaseOperator : public ZigZagObject,
                     public ZigZagParent<BaseOperator, BaseDataSource>,
                     public ZigZagParent<BaseOperator, BaseDataInput>
{
public:

    BaseOperator(const std::string& name, ZigZagObject* parent = nullptr);
    BaseOperator(ZigZagObject* parent = nullptr, const std::string& name = std::string());

    //virtual void execute() = 0;

    virtual void onFrameStart() { }
    virtual void onFrameEnd() { }

    const std::vector<BaseDataSource*>& getDataSources() const;
    const std::vector<BaseDataInput*>& getDataInputs() const;

private:

    //friend class BaseDataSource;

    //std::vector<BaseDataSource*> m_dataSources;

};
