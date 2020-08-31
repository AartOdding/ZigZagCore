#pragma once

#include <ZigZag/BaseBehaviour.hpp>

#include <array>
#include <sol/sol.hpp>


namespace ZigZag
{

    class LuaBehaviour : public BaseBehaviour
    {
    public:

        LuaBehaviour(Object* parent = nullptr, std::string_view name = std::string_view());

        virtual ~LuaBehaviour();

        virtual const char* typeName() const override { return "LuaBehaviour"; }

        void loadScript(std::string_view scriptString);

        const std::string& getScript();


        virtual void update();
        virtual void lateUpdate();

        virtual bool allowConnection(Object* other);
        virtual void connected(Object* other);
        virtual void disconnected(Object* other);

        virtual void childAdded(Object* child);
        virtual void childRemoved(Object* child);

    private:

        void resetLuaState();

        sol::state m_luaState;

        std::array<sol::function, Callbacks::COUNT> m_callbacks;

        std::string m_script;

    };

}