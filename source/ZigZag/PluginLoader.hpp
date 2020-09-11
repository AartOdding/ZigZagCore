#pragma once

#include <string>
#include <unordered_map>


namespace ZigZag
{

    class PluginLoader
    {
    public:

        virtual ~PluginLoader() = default;

        virtual void load(const std::string& pluginPath) = 0;

    };


}
