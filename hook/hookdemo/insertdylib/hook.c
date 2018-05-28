/*
 *  hook.cpp
 *  hook
 *
 *  Created by evasion on 5/27/18.
 *  Copyright © 2018 evasion. All rights reserved.
 *  cc -flat_namespace -dynamiclib -o ./bin/libhook.dylib hook.c
 */

#include <stdio.h>
#include <stdlib.h>
#import <fcntl.h>
#import <dlfcn.h>
#import <stdarg.h>

//static int (*orig_open)(const char *, int , ...) = NULL;
//static ssize_t (*orig_open)(, int , ...) = NULL;
static int (*orig_open)(const char *, int , ...) = NULL;

typedef int (*orig_open_type)(const char *, int , ...);
//typedef int (*orig_open_type)(const char *, int , ...);
//typedef int (*orig_open_type)(const char *, int , ...);



__attribute__((constructor))
void init_funcs() {
    printf("------------init funcs.-----------\n");
    void* handle = dlopen("libSystem.dylib", RTLD_NOW);
    orig_open = (orig_open_type) dlsym(handle, "open");
    if(!orig_open) {
        printf("get open addr error");
        exit(-1);
    }
    printf("------------init done.-----------\n");
}

int open(const char *path, int oflag, ...) {
    va_list ap = {0};
    mode_t mode = 0;
    
    if((oflag & O_CREAT) != 0 ) {
        va_start(ap, oflag);
        mode = va_arg(ap, int);
        va_end(ap);
        printf("calling real open('%s', %d, %d)\n", path, oflag, mode);
        return orig_open(path, oflag, mode);
    } else {
        printf("calling real open('%s', %d)\n", path, oflag);
        return orig_open(path, oflag, mode);
        
    }
}
