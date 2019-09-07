#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <dirent.h>
#include <errno.h>
#include <math.h>


// custom C code that will be callable from lua
static int l_sin (lua_State *L)
{
  double d = luaL_checknumber(L, 1);
  lua_pushnumber(L, sin(d));
  return 1;  /* number of results */
}

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

int main(int argc, char *argv[])
{
    char buff[1024];
    int err;
    lua_State *L = luaL_newstate();
    luaopen_io(L);
    luaopen_table(L);
    luaopen_os(L);
    luaopen_base(L);
    luaopen_string(L);

    // register mysin to l_sin
    lua_pushcfunction(L, l_sin);
    lua_setglobal(L, "mysin");

    lua_pushcfunction(L, l_dir);
    lua_setglobal(L, "dir");

    while (fgets(buff, sizeof(buff), stdin)) {
       err = luaL_dostring(L, buff);
       if(err) {
           printf("Error: %s\n", lua_tostring(L, -1));
           lua_pop(L, -1);
       }
    }
    return 0;
}
