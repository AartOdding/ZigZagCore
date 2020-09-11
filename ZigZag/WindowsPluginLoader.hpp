#pragma once

#include <ZigZag/PluginLoader.hpp>

#include <unordered_map>

namespace ZigZag
{

    class WindowsPluginLoader : public PluginLoader
    {
    public:

        void load(const std::string& pluginPath) override;

    private:

        std::unordered_map<std::string, void *> m_plugins;

    };

}
