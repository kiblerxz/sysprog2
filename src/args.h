#pragma once
typedef struct {
    const char *log_path;
    const char *err_path;
    int do_users;
    int do_processes;
    int show_help;
} options_t;
int parse_args(int argc, char **argv, options_t *opt, const char **err);
