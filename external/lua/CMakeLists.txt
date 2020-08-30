cmake_minimum_required(VERSION 3.0)

set(lua_headers
	lua/lapi.h
	lua/lauxlib.h
	lua/lcode.h
	lua/lctype.h
	lua/ldebug.h
	lua/ldo.h
	lua/lfunc.h
	lua/lgc.h
	lua/ljumptab.h
	lua/llex.h
	lua/llimits.h
	lua/lmem.h
	lua/lobject.h
	lua/lopcodes.h
	lua/lopnames.h
	lua/lparser.h
	lua/lprefix.h
	lua/lstate.h
	lua/lstring.h
	lua/ltable.h
	lua/ltests.h
	lua/ltm.h
	lua/lua.h
	lua/luaconf.h
	lua/lualib.h
	lua/lundump.h
	lua/lvm.h
	lua/lzio.h
)

set(lua_sources
	lua/lapi.c
	lua/lauxlib.c
	lua/lbaselib.c
	lua/lcode.c
	lua/lcorolib.c
	lua/lctype.c
	lua/ldblib.c
	lua/ldebug.c
	lua/ldo.c
	lua/ldump.c
	lua/lfunc.c
	lua/lgc.c
	lua/linit.c
	lua/liolib.c
	lua/llex.c
	lua/lmathlib.c
	lua/lmem.c                                                                                                                                                                                                   
	lua/loadlib.c
	lua/lobject.c
	lua/lopcodes.c
	lua/loslib.c
	lua/lparser.c
	lua/lstate.c
	lua/lstring.c
	lua/lstrlib.c
	lua/ltable.c
	lua/ltablib.c
	lua/ltests.c
	lua/ltm.c
	#lua/lua.c #do not use: has main()
	lua/lundump.c
	lua/lutf8lib.c
	lua/lvm.c
	lua/lzio.c
)

add_library(lua STATIC ${lua_headers} ${lua_sources})
target_include_directories(lua PUBLIC "${CMAKE_CURRENT_LIST_DIR}/lua")
