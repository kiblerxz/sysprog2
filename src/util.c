#include "util.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

bool path_writable(const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) return false;
    fclose(f);
    remove(path);
    return true;
}
void die_perror(const char *ctx) { perror(ctx); }
