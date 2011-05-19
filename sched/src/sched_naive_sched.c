/***************************************************************************
 * Copyright (C) 2011  <name of author>
 * 
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

/*!
 *  @file sched_naive_sched.c
 *
 *  @brief Very basic scheduler implementation
 *
 *  @author Joakim
 *  @date 2011-04-16
 *  @history    2011-04-10 - wrote original code - Joakim
 *              2011-04-14 - added Doxygen comments - Joakim
 *              2011-04-21 - changed name of global typedef to
                             conform to coding standard - Joakim
 *
 *  @details This implementation is used to get integration going
 *  and is kept as simple as possible to reduce complexity when focus
 *  should be on integration. It only uses the init and run functions
 *  proided by other modules and just loops over these.
 */
#ifdef NAIVE

#include <stdlib.h>
#include <stdint.h>

#include "moto_interface.h"
#include "stab_interface.h"
#include "ca_interface.h"
#include "mov_interface.h"
#include "sched_stubs.h"

#include "sched_stubs.h"

#ifdef PC
/* non-arduino includes */
#include <stdio.h>
#elif ARDUINO
/* arduino includes */
#endif /* PC ARDUINO */

#include "sched_naive_sched.h"

#define NUMBER_OF_RUN_FUNS 8
#define NUMBER_OF_INIT_FUNS 5

static int16_t system_init(sched_Fun_t funArrInit[]);
static void naive_loop(sched_Fun_t funArrRun[]);

void sched_naive_init(void){
    /* function pointers to modules init functions */
    sched_Fun_t funArrInit[] = {  
                            &protoInit,
                            &mov_init,
                            &ca_init,
                            &stab_init,
                            &moto_init };
    
    /* function pointers to modules run functions */

    sched_Fun_t funArrRun[] = {   
                            &protoRun,
                            &mov_run,
                            &protoRun,
                            &ca_run,
                            &protoRun,
                            &stab_run,
                            &protoRun,
                            &moto_run };
    
    /* call all other groups inits */
    if (system_init(funArrInit) != 1) {
        /* something went wrong during system initialization */
        #ifdef PC
            printf("Error in system initialization sequence!\n");
            exit(1);
        #endif /* PC */
        #ifdef ARDUINO
            /*  
             *  Do we have a way to give fatal error message on arduino,
             *  and exit? 
             */
            exit(1);
            
        #endif /* ARDUINO */
    }
    else {
        /* system initialization OK */
        /* call loop, pass array as argument */
        naive_loop(funArrRun);
    }
}

int16_t system_init(sched_Fun_t *funArrInit){
    int16_t i;
    int16_t res;
    
    for (i = 0; i < NUMBER_OF_INIT_FUNS; i++){
        res = (*funArrInit[i])();

        #ifdef PC
        #ifdef DEBUG
            printf("function call result: %d\n", res);
        #endif /* DEBUG */
        #endif /* PC */
    }
    return 1;
}

void naive_loop(sched_Fun_t *funArrRun){
    int16_t i;
    int16_t res;
    
    #ifdef DEBUG
        /* DEBUG flag is set, only do one loop iteration */
        for (i = 0; i < NUMBER_OF_RUN_FUNS; i++) {
            res = (*funArrRun[i])();
        }
        
    #else
        /* DEBUG flag is not set, do the normal scheduler loop */
        while (1) {
            for (i = 0; i < NUMBER_OF_RUN_FUNS; i++) {
                res = (*funArrRun[i])();
            }
        }
    #endif /* DEBUG */
}

int16_t time(void){
    int16_t currentTime;
    
    #ifdef PC
        /* call non-arduino timing functions to retrieve current time */
    #endif /* PC */
    
    #ifdef ARDUINO 
        /* call arduino specific timing functions to retrieve current time */    
    #endif /* ARDUINO */
    
    return currentTime;
}

#endif
