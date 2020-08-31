#pragma once

#include <bitset>

#include <ZigZag/Object.hpp>
#include <ZigZag/detail/ParentChild.hpp>


namespace ZigZag
{

    struct Callbacks
    {
        enum Callback
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


    class BaseBehaviour : public Object,
                          public detail::Child<BaseBehaviour, Object>
    {
    public:


        BaseBehaviour(Object* parent = nullptr, std::string_view name = std::string_view());

        virtual ~BaseBehaviour() = default;

        void setParent(Object* parent) override;

        virtual const char* typeName() const override { return "BaseBehaviour"; }

        bool implements(Callbacks::Callback callback) const;


        virtual void update() { };
        virtual void lateUpdate() { };

        virtual bool allowConnection(Object* other) { return true; };
        virtual void connected(Object* other) { };
        virtual void disconnected(Object* other) { };

        virtual void childAdded(Object* child) { };
        virtual void childRemoved(Object* child) { };

    protected:

        void setImplementedCallbacks(std::bitset<64> callbacks);
        void setCallbackImplemented(Callbacks::Callback callback, bool implemented);

    private:

        std::bitset<64> m_implementedCallbacks;

    };

}
