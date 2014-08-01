
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

extern "C"
{
	#include "lua/lauxlib.h"
	#include "lua/lualib.h"
}




// The main lua state, shared by all threads:
lua_State * g_L = NULL;





DWORD __stdcall thrExecute(LPVOID a_Param)
{
	const char * FileName = (const char *)a_Param;
	lua_State * T = lua_newthread(g_L);
	std::cout << "Executing " << FileName << std::endl;
	luaL_dofile(T, FileName);
	lua_getglobal(T, "Run");
	if (!lua_isfunction(T, -1))
	{
		std::cout << "Error in " << FileName << ": Run() function not found ('" << lua_typename(T, -1) << "' instead of 'function'). Thread terminating." << std::endl;
		return 0;
	}
	lua_call(T, 0, 0);
	std::cout << "Finished executing " << FileName << std::endl;
	// There is no call to explicitly close a thread?
	return 0;
}





int luaSleep(lua_State * L)
{
	int msec = (int)lua_tonumber(L, 1);
	Sleep(msec);
	return 0;
}





int luaPanic(lua_State * L)
{
	std::cout << "LUA PANIC!" << std::endl;
	return 0;
}





int main( int argc, char **argv)
{
	// Check params:
	if (argc == 1)
	{
		std::cout << "This program tests Lua multithreading" << std::endl;
		std::cout << "Call it with the filenames of lua code files that you want to run in parallel." << std::endl;
		return 0;
	}
	
	// Create the main lua state:
	g_L = lua_open();
	luaL_openlibs(g_L);
	lua_pushcfunction(g_L, luaSleep);
	lua_setglobal(g_L, "sleep");
	lua_atpanic(g_L, luaPanic);
	
	// Start up a new thread for each argument given:
	std::vector<DWORD> ThreadIDs;
	std::vector<HANDLE> ThreadHandles;
	for (int i = 1; i < argc; i++)
	{
		DWORD thID;
		ThreadHandles.push_back(CreateThread(NULL, 0, thrExecute, (LPVOID)argv[i], CREATE_SUSPENDED, &thID));
		ThreadIDs.push_back(thID);
	}
	for (int i = 1; i < argc; i++)
	{
		ResumeThread(ThreadHandles[i - 1]);
	}
	
	// Wait for all the threads to finish:
	WaitForMultipleObjects(ThreadHandles.size(), &ThreadHandles[0], TRUE, INFINITE);
	
	// Clean up:
	lua_close(g_L);
	std::cout << "All done, program terminating." << std::endl;
	return 0;
}




