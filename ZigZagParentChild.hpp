#pragma once

#include <vector>

template<typename PARENT_TYPE, typename CHILD_TYPE>
class ZigZagParent;

/*
 *  No virtual destructors because these classes should not be used polymorphically.
 */


template<typename CHILD_TYPE, typename PARENT_TYPE>
class ZigZagChild
{
public:

    ZigZagChild(PARENT_TYPE* parent);
    ~ZigZagChild();

protected:

    void setParent(PARENT_TYPE* parent);

private:

    friend class ZigZagParent<PARENT_TYPE, CHILD_TYPE>;

    PARENT_TYPE* m_parent = nullptr;

};



template<typename PARENT_TYPE, typename CHILD_TYPE>
class ZigZagParent
{
public:

    ~ZigZagParent();

protected:
    
    const std::vector<CHILD_TYPE*>& getChildren() const;

private:

    friend class ZigZagChild<CHILD_TYPE, PARENT_TYPE>;

    std::vector<CHILD_TYPE*> m_children;

};



template<typename CHILD_TYPE, typename PARENT_TYPE>
ZigZagChild<CHILD_TYPE, PARENT_TYPE>::ZigZagChild(PARENT_TYPE* parent)
{
    using CorrespondingParent = ZigZagParent<PARENT_TYPE, CHILD_TYPE>;

    if (m_parent)
    {
        m_parent = parent;
        m_parent->CorrespondingParent::m_children.push_back(static_cast<CHILD_TYPE*>(this));
    }
}


template<typename CHILD_TYPE, typename PARENT_TYPE>
ZigZagChild<CHILD_TYPE, PARENT_TYPE>::~ZigZagChild()
{
    using CorrespondingParent = ZigZagParent<PARENT_TYPE, CHILD_TYPE>;

    if (m_parent)
    {
        auto siblings = &m_parent->CorrespondingParent::m_children;
        auto thisPos = std::find(siblings->begin(), siblings->end(), static_cast<CHILD_TYPE*>(this));
        if (thisPos != siblings->end()) siblings->erase(thisPos);
        m_parent = nullptr;
    }
}


template<typename CHILD_TYPE, typename PARENT_TYPE>
void ZigZagChild<CHILD_TYPE, PARENT_TYPE>::setParent(PARENT_TYPE* parent)
{
    using CorrespondingParent = ZigZagParent<PARENT_TYPE, CHILD_TYPE>;

    if (m_parent)
    {
        auto siblings = &m_parent->CorrespondingParent::m_children;
        auto thisPos = std::find(siblings->begin(), siblings->end(), static_cast<CHILD_TYPE*>(this));
        if (thisPos != siblings->end()) siblings->erase(thisPos);
        m_parent = nullptr;
    }
    if (parent)
    {
        m_parent = parent;
        m_parent->CorrespondingParent::m_children.push_back(static_cast<CHILD_TYPE*>(this));
    }
}


template<typename PARENT_TYPE, typename CHILD_TYPE>
ZigZagParent<PARENT_TYPE, CHILD_TYPE>::~ZigZagParent()
{
    using CorrespondingChild = ZigZagChild<CHILD_TYPE, PARENT_TYPE>; 
    
    for (auto child : m_children)
    {
        child->CorrespondingChild::m_parent = nullptr;
    }
    m_children.clear();
}


template<typename PARENT_TYPE, typename CHILD_TYPE>
const std::vector<CHILD_TYPE*>& ZigZagParent<PARENT_TYPE, CHILD_TYPE>::getChildren() const
{
    return m_children;
}
