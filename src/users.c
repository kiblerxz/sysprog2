#include "util.h"
#define _GNU_SOURCE
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char *name, *home; } user_t;
static int cmp_user(const void *a, const void *b){
    const user_t *ua=a,*ub=b; return strcmp(ua->name, ub->name);
}
int action_users(void){
    FILE *f=fopen("/etc/passwd","r");
    if(!f){ fprintf(stderr,"error: cannot open /etc/passwd\n"); return 1; }
    size_t cap=64,n=0; user_t *arr=malloc(cap*sizeof(*arr));
    if(!arr){ fclose(f); fprintf(stderr,"error: oom\n"); return 1; }
    char *line=NULL; size_t len=0;
    while(my_getline(&line,&len,f)!=-1){
        char *save=NULL;
        char *name=strtok_r(line,":\n",&save);
        (void)strtok_r(NULL,":\n",&save);
        (void)strtok_r(NULL,":\n",&save);
        (void)strtok_r(NULL,":\n",&save);
        (void)strtok_r(NULL,":\n",&save);
        char *home=strtok_r(NULL,":\n",&save);
        if(!name||!home) continue;
        if(n==cap){ cap*=2; arr=realloc(arr,cap*sizeof(*arr)); if(!arr){ fclose(f); free(line); fprintf(stderr,"error: oom\n"); return 1; } }
        arr[n].name=strdup(name); arr[n].home=strdup(home); n++;
    }
    free(line); fclose(f);
    qsort(arr,n,sizeof(*arr),cmp_user);
    for(size_t i=0;i<n;++i){ printf("%s: %s\n",arr[i].name,arr[i].home); free(arr[i].name); free(arr[i].home); }
    free(arr); return 0;
}
