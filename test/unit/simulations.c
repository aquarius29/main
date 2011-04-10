/*
* simulations.c
*
*  Created on: 7 apr 2011
*      Author: Shan Huang
*/

#include "../../src/nav.h"

NavPathPointer nav = NULL;

/* Set up and clean up test suite */

int init_suite(point start, point end) {
	nav = init_path(start, end);
	return nav == NULL;
}

int clean_suite(void) {
	freeNavPointer(nav);
	nav = NULL;
	return 0;
}

void single_destination(void) {
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
    
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
    
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
    
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
}

void multiple_destinations(void) {
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
    
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
    
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
    
    CU_ASSERT( == set_direction( nav ));
    CU_ASSERT( == set_distance( nav ));
    CU_ASSERT( == update_path( nav ));
}