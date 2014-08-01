
cmake_minimum_required(VERSION 2.8.4)

project (LuaMultiThreaded)


SET (SRCS
	main.cpp
	Globals.cpp
	LuaUser.cpp
)


SET (LUA_SRCS
	lua/lapi.c
	lua/lauxlib.c
	lua/lbaselib.c
	lua/lcode.c
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
	lua/ltm.c
	lua/lundump.c
	lua/lvm.c
	lua/lzio.c
	lua/print.c
)


SET (HDRS
	Globals.h
	LuaUser.h
)


SET (LUA_HDRS	
	lua/lapi.h
	lua/lauxlib.h
	lua/lcode.h
	lua/ldebug.h
	lua/ldo.h
	lua/lfunc.h
	lua/lgc.h
	lua/llex.h
	lua/llimits.h
	lua/lmem.h
	lua/lobject.h
	lua/lopcodes.h
	lua/lparser.h
	lua/lstate.h
	lua/lstring.h
	lua/ltable.h
	lua/ltm.h
	lua/lua.h
	lua/luaconf.h
	lua/lualib.h
	lua/lundump.h
	lua/lvm.h
	lua/lzio.h
)


# If compiling under MSVC, disable its deprecation warnings:
if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -DLUA_USER_H="luauser.h")
endif (MSVC)


# Put Lua engine files to a separate project folder:
source_group("Lua" FILES ${LUA_SRCS})
source_group("Lua" FILES ${LUA_HDRS})

# Include this folder when searching for includes
include_directories(".")

# Name for the executable:
SET(EXECUTABLE LuaMultiThreaded)

# Create the top level executable:
add_executable(${EXECUTABLE} ${SRCS} ${HDRS} ${LUA_SRCS} ${LUA_HDRS})
