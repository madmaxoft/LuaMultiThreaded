
// LuaUser.h

// Declares the synchronization entrypoints used by Lua




/** Counter for the total number of lock operations. */
extern size_t g_NumLocks;

void LuaLock(lua_State * L);
void LuaUnlock(lua_State * L);




