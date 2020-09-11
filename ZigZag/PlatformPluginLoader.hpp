#include <ZigZag/Platform.hpp>
#include <ZigZag/UnixPluginLoader.hpp>
#include <ZigZag/WindowsPluginLoader.hpp>


namespace ZigZag
{
#if defined(ZIGZAG_UNIX_LIKE)
    using PlatformPluginLoader = UnixPluginLoader;
#elif defined(ZIGZAG_WINDOWS)
    using PlatformPluginLoader = WindowsPluginLoader;
#endif
}
