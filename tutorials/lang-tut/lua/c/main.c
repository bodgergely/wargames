#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define BUFFSZ 256

int main(int argc, char** argv)
{
    char buff[BUFFSZ];
    int error;
    // create Lua State
    lua_State *L = luaL_newstate();
    // open some of the lua libraries
    luaopen_base(L);
    luaopen_io(L);
    luaopen_os(L);
    luaopen_string(L);
    luaopen_math(L);

    while(fgets(buff, sizeof(buff), stdin) != NULL) {
        // load the instruction from stdin and execute it with pcall
        error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
                lua_pcall(L, 0, 0, 0);
        if (error) {
            // print error by converting the top element from the stack
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            // now that we printed the error we can pop it
            lua_pop(L, 1);
        }
    }

    lua_close(L);

    return 0;
}

