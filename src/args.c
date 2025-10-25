#define _GNU_SOURCE
#include "args.h"
#include <getopt.h>
#include <string.h>
int parse_args(int argc, char **argv, options_t *opt, const char **err){
    memset(opt,0,sizeof(*opt)); *err=NULL;
    static struct option L[]={
        {"users",no_argument,0,'u'},
        {"processes",no_argument,0,'p'},
        {"help",no_argument,0,'h'},
        {"log",required_argument,0,'l'},
        {"errors",required_argument,0,'e'},
        {0,0,0,0}};
    int c;
    while((c=getopt_long(argc,argv,"uphl:e:",L,NULL))!=-1){
        switch(c){
            case 'u': opt->do_users=1; break;
            case 'p': opt->do_processes=1; break;
            case 'h': opt->show_help=1; break;
            case 'l': opt->log_path=optarg; break;
            case 'e': opt->err_path=optarg; break;
            default: *err="invalid arguments"; return -1;
        }
    }
    return 0;
}
