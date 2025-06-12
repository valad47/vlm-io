#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "lualib.h"

int vlm_ReadFile(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);

    FILE *fd = fopen(filename, "r");
    if(!fd)
        return 0;

    fseek(fd, 0, SEEK_END);
    int fsize = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    char *buff = malloc(fsize+16);
    memset(buff, 0, fsize+16);

    fread(buff, 1, fsize, fd);

    lua_pushlstring(L, buff, fsize);
    fclose(fd);
    free(buff);
    return 1;
}

int vlm_WriteFile(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);
    size_t size;
    const char* data = luaL_checklstring(L, 2, &size);

    FILE *fd = fopen(filename, "w+");
    if(!fd)
        luaL_error(L, "Failed to write file: %s\n", strerror(errno));

    fwrite(data, 1, size, fd);
    fclose(fd);
    return 0;
}

char *str = NULL;

int vlm_system(lua_State* L) {
    str = luaL_checkstring(L, 1);
    pid_t pid = fork();
    if(pid == 0) {
        execl("/bin/sh", "sh", "-c", str, (char *) NULL);
        _exit(0);
    }
    return 0;
}

int vlm_write(lua_State* L) {
    for(int i = 1; i <= lua_gettop(L); i++)
        printf("%s", luaL_checkstring(L, i));
    return 0;
}
