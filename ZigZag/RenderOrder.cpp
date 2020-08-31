#include <ZigZag/RenderOrder.hpp>

#include <cassert>


static bool isStartNode(ZigZag::BaseOperator* op)
{
	if (op->getDataInputs().empty())
	{
		return true;
	}
	else
	{
		for (auto in : op->getDataInputs())
		{
			if (in->isConnected())
			{
				return false;
			}
		}
		return true;
	}
}

bool hasTurn(ZigZag::BaseOperator* op, const std::vector<ZigZag::BaseOperator*>& closedList)
{
	for (auto input : op->getDataInputs())
	{
		if (auto source = input->getConnectedOutput())
		{
			auto sourceOp = dynamic_cast<ZigZag::BaseOperator*>(source->getParent());
			// if the parent of the data source is not an operator we just say the operator
			// can be allowed to be processed. otherwise the algorithm might get into infinite
			// loops much easier.
			bool sourceOpClosed = std::find(closedList.begin(), closedList.end(), sourceOp) != closedList.end();
			
			if (!sourceOpClosed)
			{
				return false;
			}
		}
	}
	return true;
}

template<typename T>
static void removeFrom(std::vector<T>& allObjects, const std::vector<T>& objectsToRemove)
{
	for (const auto& obj : objectsToRemove)
	{
		auto it = std::find(allObjects.begin(), allObjects.end(), obj);
		assert(it != allObjects.end());
		if (it != allObjects.end())
		{
			allObjects.erase(it);
		}
	}
}


namespace ZigZag
{

RenderOrder::RenderOrder(BaseOperator* scope)
	: m_scope(scope)
{
	assert(m_scope);
	if (m_scope)
	{
		//m_callbackId = m_scope->registerChildrenCallback([this](Object*, bool) { construct(); });
		construct();
	}
}


RenderOrder::~RenderOrder()
{
	if (m_scope)
	{
		//m_scope->deregisterChildrenCallback(m_callbackId);
	}
}


const std::vector<std::vector<BaseOperator*>>& RenderOrder::order() const
{
	return m_order;
}


void RenderOrder::construct()
{
	clearBins();

	if (m_scope)
	{
		std::vector<BaseOperator*> openList = m_scope->getChildOperators();
		std::vector<BaseOperator*> closedList;
		closedList.reserve(openList.size());

		for (auto op : openList)
		{
			if (isStartNode(op))
			{
				getBin(0).push_back(op);
				closedList.push_back(op);
			}
		}
		removeFrom(openList, getBin(0));

		unsigned binIndex = 1;

		while (!openList.empty())
		{
			auto& bin = getBin(binIndex);

			for (auto op : openList)
			{
				if (hasTurn(op, closedList))
				{
					bin.push_back(op);
				}
			}

			if (bin.empty())
			{
				// The algorithm has gotten stuck :(
				// There are still operators left in the open list that need to be processed,
				// but there are no operators beign processed. for now just return.
				return;
			}
			else
			{
				removeFrom(openList, bin);
				for (auto op : bin)
				{
					closedList.push_back(op);
				}
				++binIndex;
			}
		}
		// The algorithm succesfully finished!
	}
}


std::vector<BaseOperator*>& RenderOrder::getBin(unsigned index)
{
	if (m_order.size() <= index)
	{
		m_order.resize(index + 1);
	}
	return m_order[index];
}


void RenderOrder::clearBins()
{
	// instead of clearing the m_order clear the nested vectors, so that memory is not freed,
	// and thus also doesnt need to be reallocated either.
	for (auto& vec : m_order)
	{
		vec.clear();
	}
}

}
