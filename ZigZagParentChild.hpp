#pragma once

#include <vector>
#include <type_traits>

template<typename PARENT_TYPE, typename CHILD_TYPE>
class ZigZagParent;

/*
 *  No virtual destructors because these classes should not be used as polymorphically.
 */


template<typename CHILD_TYPE, typename PARENT_TYPE>
class ZigZagChild
{
public:

    ZigZagChild(PARENT_TYPE* parent);
    ~ZigZagChild();

    void setParent(PARENT_TYPE* parent);

private:

    friend class ZigZagParent<PARENT_TYPE, CHILD_TYPE>;

    PARENT_TYPE* m_parent;

};



template<typename PARENT_TYPE, typename CHILD_TYPE>
class ZigZagParent
{
public:

    ~ZigZagParent();
    
    const std::vector<CHILD_TYPE*>& getChildren() const;

private:

    friend class ZigZagChild<CHILD_TYPE, PARENT_TYPE>;

    void addChild(CHILD_TYPE* child);
    void removeChild(CHILD_TYPE* child);

    std::vector<CHILD_TYPE*> m_children;

};



template<typename CHILD_TYPE, typename PARENT_TYPE>
ZigZagChild<CHILD_TYPE, PARENT_TYPE>::ZigZagChild(PARENT_TYPE* parent)
    : m_parent(parent)
{
    if (m_parent)
    {
        m_parent->ZigZagParent<PARENT_TYPE, CHILD_TYPE>::addChild(static_cast<CHILD_TYPE*>(this));
    }
}


template<typename CHILD_TYPE, typename PARENT_TYPE>
ZigZagChild<CHILD_TYPE, PARENT_TYPE>::~ZigZagChild()
{
    if (m_parent)
    {
        m_parent->ZigZagParent<PARENT_TYPE, CHILD_TYPE>::removeChild(static_cast<CHILD_TYPE*>(this));
        m_parent = nullptr;
    }
}


template<typename CHILD_TYPE, typename PARENT_TYPE>
void ZigZagChild<CHILD_TYPE, PARENT_TYPE>::setParent(PARENT_TYPE* parent)
{
    if (m_parent)
    {
        m_parent->ZigZagParent<PARENT_TYPE, CHILD_TYPE>::removeChild(static_cast<CHILD_TYPE*>(this));
        m_parent = nullptr;
    }
    if (parent)
    {
        m_parent = parent;
        m_parent->ZigZagParent<PARENT_TYPE, CHILD_TYPE>::addChild(static_cast<CHILD_TYPE*>(this));
    }
}


template<typename PARENT_TYPE, typename CHILD_TYPE>
ZigZagParent<PARENT_TYPE, CHILD_TYPE>::~ZigZagParent()
{
    for (auto child : m_children)
    {
        child->ZigZagChild<CHILD_TYPE, PARENT_TYPE>::m_parent = nullptr;
    }
    m_children.clear();
}


template<typename PARENT_TYPE, typename CHILD_TYPE>
const std::vector<CHILD_TYPE*>& ZigZagParent<PARENT_TYPE, CHILD_TYPE>::getChildren() const
{
    return m_children;
}


template<typename PARENT_TYPE, typename CHILD_TYPE>
void ZigZagParent<PARENT_TYPE, CHILD_TYPE>::addChild(CHILD_TYPE* child)
{
    m_children.push_back(child);
}


template<typename PARENT_TYPE, typename CHILD_TYPE>
void ZigZagParent<PARENT_TYPE, CHILD_TYPE>::removeChild(CHILD_TYPE* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);

    if (it != m_children.end())
    {
        m_children.erase(it);
    }
}
