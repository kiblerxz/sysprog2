#include "util.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

bool path_writable(const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) return false;
    fclose(f);
    remove(path);
    return true;
}

void die_perror(const char *ctx) { perror(ctx); }

/* Реализация getline-подобной функции */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    if (!lineptr || !n || !stream) { errno = EINVAL; return -1; }
    if (*lineptr == NULL || *n == 0) {
        *n = 128;
        *lineptr = (char*)malloc(*n);
        if (!*lineptr) { errno = ENOMEM; return -1; }
    }
    size_t len = 0;
    for (;;) {
        int c = fgetc(stream);
        if (c == EOF) {
            if (len == 0) return -1;
            break;
        }
        if (len + 1 >= *n) { // +1 для '\0'
            size_t newn = (*n) * 2;
            char *p = (char*)realloc(*lineptr, newn);
            if (!p) { errno = ENOMEM; return -1; }
            *lineptr = p; *n = newn;
        }
        (*lineptr)[len++] = (char)c;
        if (c == '\n') break;
    }
    (*lineptr)[len] = '\0';
    return (ssize_t)len;
}
