#include "help.h"
#include <stdio.h>
int action_help(const char *prog){
    printf(
        "Usage: %s [OPTIONS]\n"
        "  -u, --users            List users and home directories (sorted)\n"
        "  -p, --processes        List running processes (sorted by PID)\n"
        "  -l, --log PATH         Redirect stdout to PATH\n"
        "  -e, --errors PATH      Redirect stderr to PATH\n"
        "  -h, --help             Show this help and exit\n", prog);
    return 0;
}
