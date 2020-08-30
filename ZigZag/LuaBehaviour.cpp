#include <ZigZag/LuaBehaviour.hpp>


#include <iostream>

namespace ZigZag
{

    LuaBehaviour::LuaBehaviour(Object* parent, std::string_view name)
        : BaseBehaviour(parent, name)
    {
        std::cout << "LuaBehaviour constructor" << std::endl;



        loadScript(R"(

function update() 
    print('bark bark bark!')
end

)");

        update();
        update();
        update();

    }

    LuaBehaviour::~LuaBehaviour()
    {
        std::cout << "LuaBehaviour destructor" << std::endl;
    }


    void LuaBehaviour::loadScript(std::string_view scriptString)
    {
        resetLuaState();
        m_luaState.script(scriptString);
        for (int i = 0; i < Callbacks::COUNT; ++i)
        {
            m_callbacks[i] = m_luaState[Callbacks::toString(i)];
        }
    }

    void LuaBehaviour::loadScriptFile(const std::string& scriptFileName)
    {
        resetLuaState();
        m_luaState.script_file(scriptFileName);
        for (int i = 0; i < Callbacks::COUNT; ++i)
        {
            m_callbacks[i] = m_luaState[Callbacks::toString(i)];
        }
    }


    void LuaBehaviour::update()
    {
        if (m_callbacks[Callbacks::Update].valid())
        {
            m_callbacks[Callbacks::Update]();
        }
    }

    void LuaBehaviour::lateUpdate()
    {
        if (m_callbacks[Callbacks::LateUpdate].valid())
        {
            m_callbacks[Callbacks::LateUpdate]();
        }
    }

    bool LuaBehaviour::allowConnection(Object* other)
    {
        if (m_callbacks[Callbacks::AllowConnection].valid())
        {
            m_callbacks[Callbacks::AllowConnection]();
        }
        return true;
    }

    void LuaBehaviour::connected(Object* other)
    {
        if (m_callbacks[Callbacks::Connected].valid())
        {
            m_callbacks[Callbacks::Connected]();
        }
    }

    void LuaBehaviour::disconnected(Object* other)
    {
        if (m_callbacks[Callbacks::Disconnected].valid())
        {
            m_callbacks[Callbacks::Disconnected]();
        }
    }

    void LuaBehaviour::childAdded(Object* child)
    {
        if (m_callbacks[Callbacks::ChildAdded].valid())
        {
            m_callbacks[Callbacks::ChildAdded]();
        }
    }

    void LuaBehaviour::childRemoved(Object* child)
    {
        if (m_callbacks[Callbacks::ChildRemoved].valid())
        {
            m_callbacks[Callbacks::ChildRemoved]();
        }
    }

    void LuaBehaviour::resetLuaState()
    {
        for (auto& fn : m_callbacks)
        {
            fn = sol::function();
        }
        m_luaState = sol::state();
        m_luaState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table, sol::lib::string);
    }

}
