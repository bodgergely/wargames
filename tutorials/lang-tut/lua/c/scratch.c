#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lua.h>
#include <luaconf.h>
#include <lauxlib.h>
#include <lualib.h>

#define BUFFSZ 256

int handle_panic(lua_State *L) 
{
    fprintf(stderr, "Panic!!! Reason: %s\n", lua_tostring(L, -1));
    exit(-1);
}

int main(int argc, char** argv)
{
    char buff[BUFFSZ];
    int err;
    // create Lua State
    lua_State *L = luaL_newstate();
    if(!lua_atpanic(L, handle_panic)) {
        printf("Failed to set panic handler!\n");
    }
    // open some of the lua libraries
    luaopen_base(L);
    luaopen_io(L);
    luaopen_os(L);
    luaopen_string(L);
    luaopen_math(L);
   
    strcpy(buff, "function foo() return 89 end; res = foo()");

    fprintf(stdout, "gettop: %d\n", lua_gettop(L));
    err = luaL_loadbuffer(L, buff, strlen(buff), "line");
    if (err) {
        fprintf(stderr, "Error compiling %s, reason: %s\n",buff, lua_tostring(L, -1));
        lua_pop(L, 1);
        lua_close(L);
        exit(-1);
    }

    err = lua_type(L, -1);
    fprintf(stdout, "%s\n", lua_typename(L, err));
    fprintf(stdout, "gettop: %d\n", lua_gettop(L));
    err = lua_pcall(L, 0, 0, 0);
    if(err) {
        fprintf(stderr, "Error running %s, reason: %s\n", buff, lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    err = lua_type(L, -1);
    fprintf(stdout, "%s\n", lua_typename(L, err));

    err = lua_getglobal(L, "res");
    err = lua_tonumber(L, -1);
    printf("Result: %d\n", err);


    lua_pushstring(L, "MarcikaJo");
    fprintf(stdout, "gettop: %d\n", lua_gettop(L));
    fprintf(stdout, "%d\n", lua_rawlen(L, -1));
    err = lua_type(L, -1);
    fprintf(stdout, "%s\n", lua_typename(L, err));

    lua_close(L);

    if(err) {
        exit(-1);
    } 

    return 0;
}

