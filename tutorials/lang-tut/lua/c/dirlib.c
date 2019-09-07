#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <dirent.h>
#include <errno.h>
#include <string.h>



static int l_dir (lua_State *L) 
{
  DIR *dir;
  struct dirent *entry;
  int i;
  const char *path = luaL_checkstring(L, 1);

  /* open directory */
  dir = opendir(path);
  if (dir == NULL) {  /* error opening the directory? */
    lua_pushnil(L);  /* return nil and ... */
    lua_pushstring(L, strerror(errno));  /* error message */
    return 2;  /* number of results */
  }

  /* create result table */
  lua_newtable(L);
  i = 1;
  while ((entry = readdir(dir)) != NULL) {
    lua_pushnumber(L, i++);  /* push key */
    lua_pushstring(L, entry->d_name);  /* push value */
    lua_settable(L, -3);
  }

  closedir(dir);
  return 1;  /* table is already on top */
}


static const struct luaL_reg dirlib [] = {
  {"dir", l_dir},
  {NULL, NULL}  /* sentinel */
};


// the entry point to the library
int luaopen_dirlib (lua_State *L) {
  luaL_openlib(L, "dirlib", dirlib, 0);
  return 1;
}


