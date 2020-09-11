
namespace ZigZag
{
    namespace detail
    {

        template<typename PARENT_TYPE, typename CHILD_TYPE>
        Parent<PARENT_TYPE, CHILD_TYPE>::~Parent()
        {
            using CorrespondingChild = Child<CHILD_TYPE, PARENT_TYPE>;

            for (auto child : m_children)
            {
                child->CorrespondingChild::m_parent = nullptr;
            }
            m_children.clear();
        }


        template<typename PARENT_TYPE, typename CHILD_TYPE>
        const std::vector<CHILD_TYPE*>& Parent<PARENT_TYPE, CHILD_TYPE>::getChildren() const
        {
            return m_children;
        }

    }
}
