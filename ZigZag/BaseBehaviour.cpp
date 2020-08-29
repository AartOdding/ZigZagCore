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

}
