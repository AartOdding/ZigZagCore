#pragma once

#include <vector>

#include <ZigZag/BaseOperator.hpp>


namespace ZigZag
{

/*
 * The RenderOrder class managers the order in which the children of a given operator are rendered.
 * It will make sure to remove all objects that are also removed from the operator. It is however
 * important that the main operator that is being tracked remains valid. The RenderOrder object is
 * not allowed to outlive the operator!
 */
class RenderOrder
{
public:

    explicit RenderOrder(BaseOperator* scope);
    ~RenderOrder();

    RenderOrder(const RenderOrder&) = delete;
    RenderOrder(RenderOrder&&) = delete;

    const std::vector<std::vector<BaseOperator*>>& order() const;

    void construct();

private:

    std::vector<BaseOperator*>& getBin(unsigned index);
    void clearBins();

	BaseOperator* m_scope;
    CallbackId m_callbackId;
	
    std::vector<std::vector<BaseOperator*>> m_order;

};

}
