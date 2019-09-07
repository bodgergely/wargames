#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


void load(char *filename, int *width, int *height) {
  lua_State *L = luaL_newstate();
  luaopen_base(L);
  luaopen_io(L);
  luaopen_string(L);
  luaopen_math(L);

  if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
    luaL_error(L, "cannot run configuration file: %s",
             lua_tostring(L, -1));

  lua_getglobal(L, "width");
  lua_getglobal(L, "height");
  if (!lua_isnumber(L, -2))
    luaL_error(L, "`width' should be a number\n");
  if (!lua_isnumber(L, -1))
    luaL_error(L, "`height' should be a number\n");
  *width = (int)lua_tonumber(L, -2);
  *height = (int)lua_tonumber(L, -1);

  lua_close(L);
}

int main(int argc, char *argv[])
{
    int width;
    int height;
    load("window.lua", &width, &height);
    printf("Window size has been set to:\n");
    printf("width: %d\n", width);
    printf("height: %d\n", height);
    return 0;
}
