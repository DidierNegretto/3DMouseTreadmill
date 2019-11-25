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

static inline bool display (bool correct, const char *name){
    if(correct == true){
        printf("\t["GREEN "OK" END"] ");
        printf(name);
        printf(GREEN " DONE SUCCESSFULY\n" END);
    }
    else{
       printf("["RED "ERR" END"] ");
       printf(name);
       printf(RED " PERFORMED INCORRECTLY OR NOT AT ALL\n" END);
    }
    return correct;
}


#endif /* DISPLAY_H_ */
