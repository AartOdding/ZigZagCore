#pragma once

#include <ZigZag/Object.hpp>
#include <ZigZag/detail/ParentChild.hpp>


namespace ZigZag
{

class BaseBehaviour : public Object,
                      public detail::Child<BaseBehaviour, Object>
{
public:

    BaseBehaviour(Object* parent = nullptr, std::string_view name = std::string_view());

    virtual ~BaseBehaviour() = default;

    void setParent(Object* parent) override;

    virtual const char* typeName() const override { return "BaseBehaviour"; }

    virtual void update() = 0;
    virtual void lateUpdate() = 0;

    virtual bool allowConnection(Object* other) = 0;
    virtual void connected(Object* other) = 0;
    virtual void disconnected(Object* other) = 0;

    virtual void childAdded(Object* child) = 0;
    virtual void childRemoved(Object* child) = 0;

protected:

    struct Callbacks
    {
        enum
        {
            Update = 0,
            LateUpdate = 1,
            AllowConnection = 2,
            Connected = 3,
            Disconnected = 4,
            ChildAdded = 5,
            ChildRemoved = 6,
            COUNT = 7
        };

        static const char* toString(int callback)
        {
            switch (callback)
            {
            case Callbacks::Update:
                return "update";
            case Callbacks::LateUpdate:
                return "lateUpdate";
            case Callbacks::AllowConnection:
                return "allowConnection";
            case Callbacks::Connected:
                return "connected";
            case Callbacks::Disconnected:
                return "disconnected";
            case Callbacks::ChildAdded:
                return "childAdded";
            case Callbacks::ChildRemoved:
                return "childRemoved";
            }
            return "";
        }
    };



};

}
