/*! \file display.h
\brief Header and implementation of display function for unit tests

\author Didier Negretto
*/

#ifndef DISPLAY_H_
#define DISPLAY_H_

/* DEFINES COLORS FOR DISPLAY IN TERMINAL */
/*!
\def RED
\brief Prints text between RED and \ref END in red color
*/
#define RED     "\x1b[31m"
/*!
\def GREEN
\brief Prints text between GREEN and \ref END in green color
*/
#define GREEN   "\x1b[32m"
/*!
\def END
\brief stops printin using color.
*/
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
/*!
 \fn static inline bool display (bool correct, const char *name)
 \param correct 1 if the test is successfull 0 if it is not
 \param name pointer to string with the name of the test that is run
 \return The result of the test (1 if correct == 1, 0 if correct == 0).
 \brief This function prints on the terminal is the test is passed successfully
 or not
 */
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
