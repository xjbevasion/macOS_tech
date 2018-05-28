//
//  main.c
//  dylgdemo
//
//  Created by evasion on 5/27/18.
//  Copyright © 2018 evasion. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#import <fcntl.h>



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");

    int fd = open(argv[0], O_RDONLY);
    uint32_t magic_number = 0;
    read(fd, (void*)&magic_number, 4);
    printf("Mach-O Magic number:%x\n", magic_number);
    
    close(fd);
    
    return 0;
}
