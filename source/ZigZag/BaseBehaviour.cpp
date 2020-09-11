#include <ZigZag/BaseBehaviour.hpp>



namespace ZigZag
{

    BaseBehaviour::BaseBehaviour(Object* parent, std::string_view name)
        : Object(parent, name),
          Child<BaseBehaviour, Object>(parent)
    {

    }


    void BaseBehaviour::setParent(Object* parent)
    {
        Object::setParent(parent);
        Child<BaseBehaviour, Object>::setParent(parent); // no need to cast, already object type.
    }


    bool BaseBehaviour::implements(Callbacks::Callback callback) const
    {
        return m_implementedCallbacks.test(callback);
    }


    void BaseBehaviour::setImplementedCallbacks(std::bitset<64> callbacks)
    {
        m_implementedCallbacks = callbacks;
    }


    void BaseBehaviour::setCallbackImplemented(Callbacks::Callback callback, bool implemented)
    {
        m_implementedCallbacks.set(callback, implemented);
    }

}
