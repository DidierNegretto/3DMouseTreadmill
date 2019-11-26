/*
 * display.h
 *
 *  Created on: Nov 24, 2019
 *      Author: Didier
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define END   "\x1b[0m"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef COLOR
static inline bool display (bool correct, const char *name){
    if(correct == 1){
        printf("    ["GREEN "OK" END"] ");
        printf(name);
        printf(GREEN " DONE SUCCESSFULY\n" END);
        return 1;
    }
    else{
       printf("["RED "NO" END"]     ");
       printf(name);
       printf(RED " PERFORMED INCORRECTLY OR NOT AT ALL\n" END);
       return 0;
    }
    return 0;
}
#else

static inline bool display (bool correct, const char *name){
    if(correct == 1){
        printf("    [OK] ");
        printf("%s", name);
        printf(" DONE SUCCESSFULY\n");
        return 1;
    }
    else{
       printf("[NO]     ");
       printf("%s", name);
       printf(" PERFORMED INCORRECTLY OR NOT AT ALL\n");
       return 0;
    }
    return 0;
}
#endif
#endif /* DISPLAY_H_ */
