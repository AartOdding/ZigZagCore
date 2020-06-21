#include <ZigZag/Object.hpp>
#include <ZigZag/ObjectSelection.hpp>

#include <stdexcept>

using namespace ZigZag;



ObjectSelection::ObjectSelection(Object* rootObject)
    : m_rootObject(rootObject)
{ }


void ObjectSelection::setRootObject(Object* rootObject)
{
    m_rootObject = rootObject;
    clearInvalidObjects();
}


void ObjectSelection::setSelected(Object* object, bool selected)
{
    if (object != m_rootObject && !object->isChildOf(m_rootObject, false))
    {
        throw std::runtime_error("Can only add descendants of the selection root object to the selection.");
    }
    bool alreadySelected = isSelected(object);

    if (selected && !alreadySelected)
    {
        m_selectedObjects.emplace(object);
    }
    else if (!selected && alreadySelected)
    {
        m_selectedObjects.erase(object);
    }
}


void ObjectSelection::toggleSelected(Object* object)
{
    setSelected(object, !isSelected(object));
}


bool ObjectSelection::isSelected(Object* object) const
{
    return m_selectedObjects.count(object);
}


bool ObjectSelection::isIndirectlySelected(Object* object) const
{
    while (object)
    {
        if (isSelected(object))
        {
            return true;
        }
        object = object->getParent();
    }
    return false;
}


void ObjectSelection::clearSelection()
{
    m_selectedObjects.clear();
}


void ObjectSelection::clearInvalidObjects()
{
    if (!m_selectedObjects.empty())
    {
        std::vector<ZigZag::Object*> toDelete;
        std::unordered_set<ZigZag::Object*> allowed;
        addToSet(m_rootObject, allowed);

        for (auto selected : m_selectedObjects)
        {
            if (!allowed.count(selected))
            {
                toDelete.emplace_back(selected);
            }
        }

        for (auto del : toDelete)
        {
            m_selectedObjects.erase(del);
        }
    }
}


const std::unordered_set<ZigZag::Object*>& ObjectSelection::getSelection()
{
    return m_selectedObjects;
}


void ObjectSelection::addToSet(ZigZag::Object* object, std::unordered_set<ZigZag::Object*>& set)
{
    set.emplace(object);
    for (auto child : object->getChildObjects())
    {
        addToSet(child, set);
    }
}
