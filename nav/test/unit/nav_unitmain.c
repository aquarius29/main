/*
* unitmain.c
*
*  Created on: 7 apr 2011
*      Author: Shan Huang
*/

#include "CUnit/Basic.h"
#include "nav_itparser.c"
#include "nav_itdijkstra.c"
#include "nav_itastar.c"
#include "nav_itsimulation.c"

/* Set up and clean up test suite */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

int main() {
    CU_pSuite xmlSuite = NULL;
    CU_pSuite dijkstraSuite = NULL;
    CU_pSuite astarSuite = NULL;
    CU_pSuite indoorNavSuite = NULL;

  /* Initialize the CUnit test registry */
    if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

  /* Add a suite to the registry */
    xmlSuite = CU_add_suite("XML Parsing", init_suite, clean_suite);
    dijkstraSuite = CU_add_suite("Dijkstra", init_suite, clean_suite);
    astarSuite = CU_add_suite("AStar", init_suite, clean_suite);
    indoorNavSuite = CU_add_suite("Indoor Navigation", init_suite, clean_suite);
    
    if(	NULL == xmlSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

  /* Add tests to suite */
    // if(  NULL == CU_add_test(xmlSuite, "Parse map", test_parse_xml)
    // ) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }
    // 
    // if(  NULL == CU_add_test(xmlSuite, "Dijkstra", test_dijkstra_1)
    //     // || NULL == CU_add_test(xmlSuite, "Dijkstra invalid tile", test_dijkstra_2)
    // ) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }
    
    // if(  NULL == CU_add_test(xmlSuite, "AStar", test_astar_1)
    //     // || NULL == CU_add_test(xmlSuite, "Astar invalid tile", test_astar_2)
    // ) {
    //     CU_cleanup_registry();
    //     return CU_get_error();
    // }
    
    if(	NULL == CU_add_test(xmlSuite, "Normal Flight", test_indoor_navigation_1)
        // || NULL == CU_add_test(xmlSuite, "Flight with Collision Avoidance", test_indoor_navigation_2)
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

  /* Run all tests using the CUnit Console interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}