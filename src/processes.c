#include "util.h"
#define _GNU_SOURCE
#include "processes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

typedef struct { long pid; char *name; } proc_t;
static int cmp_pid(const void *a,const void *b){
    const proc_t *pa=a,*pb=b; return (pa->pid>pb->pid)-(pa->pid<pb->pid);
}
int action_processes(void){
    DIR *d=opendir("/proc"); if(!d){ fprintf(stderr,"error: cannot open /proc\n"); return 1; }
    size_t cap=256,n=0; proc_t *arr=malloc(cap*sizeof(*arr));
    if(!arr){ closedir(d); fprintf(stderr,"error: oom\n"); return 1; }
    struct dirent *e;
    while((e=readdir(d))){
        const char *s=e->d_name; if(!isdigit((unsigned char)*s)) continue;
        for(const char *p=s;*p;++p) if(!isdigit((unsigned char)*p)){ s=NULL; break; }
        if(!s) continue;
        long pid=atol(e->d_name);
        char path[64]; snprintf(path,sizeof(path),"/proc/%ld/comm",pid);
        FILE *f=fopen(path,"r"); if(!f) continue;
        char *line=NULL; size_t len=0; ssize_t r=my_getline(&line,&len,f); fclose(f);
        if(r<=0){ free(line); continue; } if(line[r-1]=='\n') line[r-1]=0;
        if(n==cap){ cap*=2; arr=realloc(arr,cap*sizeof(*arr)); if(!arr){ fprintf(stderr,"error: oom\n"); closedir(d); return 1; } }
        arr[n].pid=pid; arr[n].name=line; n++;
    }
    closedir(d);
    qsort(arr,n,sizeof(*arr),cmp_pid);
    for(size_t i=0;i<n;++i){ printf("%ld %s\n",arr[i].pid,arr[i].name); free(arr[i].name); }
    free(arr); return 0;
}
