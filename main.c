#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "lualib.h"

int vlm_ReadFile(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);

    FILE *fd = fopen(filename, "r");
    if(!fd)
        luaL_error(L, "Failed to read file: %s\n", strerror(errno));

    fseek(fd, 0, SEEK_END);
    int fsize = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    char *buff = malloc(fsize+16);
    memset(buff, 0, fsize+16);

    fread(buff, 1, fsize, fd);
    fclose(fd);

    lua_pushstring(L, buff);
    free(buff);
    return 1;
}

int vlm_WriteFile(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);
    const char* data = luaL_checkstring(L, 2);

    FILE *fd = fopen(filename, "w+");
    if(!fd)
        luaL_error(L, "Failed to write file: %s\n", strerror(errno));

    fwrite(data, 1, strlen(data), fd);
    fclose(fd);
    return 0;
}
