/*
* simulations.c
*
*  Created on: 7 apr 2011
*      Author: Shan Huang
*/

#include "../../src/indoor/path_structure.h"
#include "../../src/indoor/indoor_algorithms.h"

/* Set up and clean up test suite */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

/* Test cases */

void test_init_list(void)
{
    position a, b;
    a.x = 1;
    a.y = 1;
    b.x = 9;
    b.y = 5;
    // init_path(a, b);
    CU_ASSERT(a.x == 1);
    CU_ASSERT(a.y == 1);
}