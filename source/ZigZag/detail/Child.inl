#include <algorithm>


namespace ZigZag
{
    namespace detail
    {

        template<typename CHILD_TYPE, typename PARENT_TYPE>
        Child<CHILD_TYPE, PARENT_TYPE>::Child(PARENT_TYPE* parent)
        {
            using CorrespondingParent = Parent<PARENT_TYPE, CHILD_TYPE>;

            if (parent)
            {
                m_parent = parent;
                m_parent->CorrespondingParent::m_children.push_back(static_cast<CHILD_TYPE*>(this));
            }
        }


        template<typename CHILD_TYPE, typename PARENT_TYPE>
        Child<CHILD_TYPE, PARENT_TYPE>::~Child()
        {
            using CorrespondingParent = Parent<PARENT_TYPE, CHILD_TYPE>;

            if (m_parent)
            {
                auto siblings = &m_parent->CorrespondingParent::m_children;
                auto thisPos = std::find(siblings->begin(), siblings->end(), static_cast<CHILD_TYPE*>(this));
                if (thisPos != siblings->end()) siblings->erase(thisPos);
                m_parent = nullptr;
            }
        }


        template<typename CHILD_TYPE, typename PARENT_TYPE>
        void Child<CHILD_TYPE, PARENT_TYPE>::setParent(PARENT_TYPE* parent)
        {
            using CorrespondingParent = Parent<PARENT_TYPE, CHILD_TYPE>;

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

    }
}
