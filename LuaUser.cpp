
// LuaUser.cpp

#include "Globals.h"

extern "C"
{
	#include "lua/lauxlib.h"
	#include "lua/lualib.h"
}

#include "LuaUser.h"





// The critical section used to synchronize access to Lua state information:
class cCS
{
public:
	cCS(void)
	{
		InitializeCriticalSection(&m_CS);
	}
	
	~cCS()
	{
		DeleteCriticalSection(&m_CS);
	}
	
	void Enter(void)
	{
		EnterCriticalSection(&m_CS);
	}
	
	void Leave(void)
	{
		LeaveCriticalSection(&m_CS);
	}
	
protected:
	CRITICAL_SECTION m_CS;
} g_CS;





size_t g_NumLocks = 0;





void LuaLock(lua_State * L)
{
	g_CS.Enter();
	g_NumLocks += 1;
}





void LuaUnlock(lua_State * L)
{
	g_CS.Leave();
}




