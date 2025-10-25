#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "users.h"
#include "processes.h"
#include "help.h"
#include "io_redirect.h"

int main(int argc, char **argv){
    options_t opt; const char *err=NULL;
    if(parse_args(argc,argv,&opt,&err)<0){
        fprintf(stderr,"error: %s (use -h for help)\n", err); return 2;
    }
    if(opt.err_path && !redirect_stderr_to(opt.err_path)) return 3;
    if(opt.log_path && !redirect_stdout_to(opt.log_path)) return 3;

    if(opt.show_help || (!opt.do_users && !opt.do_processes))
        return action_help(argv[0]);

    int rc=0;
    if(opt.do_users) rc |= action_users();
    if(opt.do_processes) rc |= action_processes();
    return rc?1:0;
}
