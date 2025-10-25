#include "io_redirect.h"
#include "util.h"
#include <stdio.h>
bool redirect_stdout_to(const char *path) {
    if (!path_writable(path)) { fprintf(stderr,"error: cannot write to '%s'\n", path); return false; }
    if (!freopen(path, "w", stdout)) { die_perror("freopen(stdout)"); return false; }
    return true;
}
bool redirect_stderr_to(const char *path) {
    if (!path_writable(path)) { fprintf(stderr,"error: cannot write to '%s'\n", path); return false; }
    if (!freopen(path, "w", stderr)) { die_perror("freopen(stderr)"); return false; }
    return true;
}
