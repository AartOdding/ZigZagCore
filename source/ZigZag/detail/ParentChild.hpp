#pragma once

#include <vector>


namespace ZigZag
{
    namespace detail
    {

        template<typename PARENT_TYPE, typename CHILD_TYPE>
        class Parent;



        template<typename CHILD_TYPE, typename PARENT_TYPE>
        class Child
        {
        public:

            Child(PARENT_TYPE* parent);
            ~Child(); // Non-virtual: Class should not be used polymorphically.

        protected:

            void setParent(PARENT_TYPE* parent);

        private:

            friend class Parent<PARENT_TYPE, CHILD_TYPE>;

            PARENT_TYPE* m_parent = nullptr;

        };



        template<typename PARENT_TYPE, typename CHILD_TYPE>
        class Parent
        {
        public:

            ~Parent(); // Non-virtual: Class should not be used polymorphically.

        protected:

            const std::vector<CHILD_TYPE*>& getChildren() const;

        private:

            friend class Child<CHILD_TYPE, PARENT_TYPE>;

            std::vector<CHILD_TYPE*> m_children;

        };


    }
}

#include <ZigZag/detail/Child.inl>
#include <ZigZag/detail/Parent.inl>
