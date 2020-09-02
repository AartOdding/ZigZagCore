#pragma once

#include <ZigZag/BaseBehaviour.hpp>

#include <array>
#include <unordered_map>
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


        virtual void update() override;
        virtual void lateUpdate() override;

        virtual bool allowConnection(Object* other) override;
        virtual void connected(Object* other) override;
        virtual void disconnected(Object* other) override;

        virtual void childAdded(Object* child) override;
        virtual void childRemoved(Object* child) override;

    private:

        void resetLuaState();

        sol::state m_luaState;

        std::array<sol::function, Callbacks::COUNT> m_callbacks;

        std::string m_script;

    };

}