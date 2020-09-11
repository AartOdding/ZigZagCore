#pragma once

#include <unordered_set>



namespace ZigZag
{

    class Object;


    class ObjectSelection
    {
    public:

        // rootObject needs to outlive the ObjectSelection instance. 
        ObjectSelection(Object* rootObject);

        void setRootObject(Object* rootObject);

        void setSelected(Object* object, bool selected);
        void toggleSelected(Object* object);

        // returns true if the object is directly selected.
        bool isSelected(Object* object) const;

        // returns true if the object is directly or indirectly seleted.
        bool isIndirectlySelected(Object* object) const;

        void clearSelection();

        // will remove all objects from the selection that have been deleted, or
        // are no longer descendants of the root_object.
        void clearInvalidObjects();

        const std::unordered_set<ZigZag::Object*>& getSelection();

    private:

        // Will recursively add the given object and its children to the set.
        static void addToSet(ZigZag::Object* object, std::unordered_set<ZigZag::Object*>& set);

        Object* m_rootObject;

        std::unordered_set<ZigZag::Object*> m_selectedObjects;

    };

}


