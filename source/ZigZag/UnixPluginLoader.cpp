#include <ZigZag/UnixPluginLoader.hpp>
#include <ZigZag/Platform.hpp>

#include <iostream>
#include <filesystem>

#ifdef ZIGZAG_UNIX_LIKE
    #include <dlfcn.h>
#endif

typedef void (*getPluginDataSources_t)(int*, const char ** );

namespace ZigZag
{

    void UnixPluginLoader::load(const std::string& pluginPath)
    {
#ifdef ZIGZAG_UNIX_LIKE
        if (std::filesystem::exists(pluginPath))
        {
            if (m_plugins.count(pluginPath) == 0)
            {
                auto plugin = dlopen(pluginPath.c_str(), RTLD_LAZY);
                if (plugin)
                {
                    m_plugins[pluginPath] = plugin;
                    std::cout << "plugin loaded" << std::endl;
                    auto get = dlsym(plugin, "getPluginDataSources");
                    void (*fn)(int*, IDataSourceFactory**);
                }
                auto error = dlerror();
                if (error)
                {
                    std::cout << error << std::endl;
                }
            }
            else
            {
                // plugin has already been loaded
            }
        }
        else
        {
            // plugin does not exist
        }
#endif
    }


}
