#include "../../src/nav_indoorstructure.h"
#include "../../src/nav_indooralgorithms.h"

void test_dijkstra_1() {
    position a, b;
    positionList projectedPath;
    
    a.x = 1;
    a.y = 1;
    b.x = 9;
    b.y = 5;    
    projectedPath = indoorDijkstra(&a, &b);
    
    // CU_ASSERT(selected_tiles_are_valid_for_dijkstra(&a, &b) == 1);
    CU_ASSERT(projectedPath.list[0].lon == 162);
    CU_ASSERT(projectedPath.list[0].lat == 162);
    CU_ASSERT(projectedPath.list[1].lon == 162);
    CU_ASSERT(projectedPath.list[1].lat == 270);
    CU_ASSERT(projectedPath.list[2].lon == 270);
    CU_ASSERT(projectedPath.list[2].lat == 270);
    CU_ASSERT(projectedPath.list[3].lon == 378);
    CU_ASSERT(projectedPath.list[3].lat == 270);
    CU_ASSERT(projectedPath.list[4].lon == 486);
    CU_ASSERT(projectedPath.list[4].lat == 270);
    CU_ASSERT(projectedPath.list[5].lon == 594);
    CU_ASSERT(projectedPath.list[5].lat == 378);
    CU_ASSERT(projectedPath.list[6].lon == 702);
    CU_ASSERT(projectedPath.list[6].lat == 486);
    CU_ASSERT(projectedPath.list[7].lon == 810);
    CU_ASSERT(projectedPath.list[7].lat == 486);
    CU_ASSERT(projectedPath.list[8].lon == 918);
    CU_ASSERT(projectedPath.list[8].lat == 486);
    CU_ASSERT(projectedPath.list[9].lon == 1026);
    CU_ASSERT(projectedPath.list[9].lat == 594);   
}

// void test_dijkstra_2() {
//     position a, b;
//     position_list projectedPath;
//         
//     a.x = 1;
//     a.y = 1;
//     b.x = 10;
//     b.y = 5;    
//     projectedPath = indoor_dijkstra(&a, &b);
//     
//     CU_ASSERT(selected_tiles_are_valid_for_dijkstra(&a, &b) == 0);
// }