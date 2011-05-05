#include "../../src/indoor/path_structure.h"
#include "../../src/indoor/indoor_algorithms.h"

void test_astar_1() {
    position a, b;
    position_list projected_path;
    
    a.x = 1;
    a.y = 1;
    b.x = 9;
    b.y = 5;    
    projected_path = indoor_astar(&a, &b);
           
    CU_ASSERT(selected_tiles_are_valid_for_astar(&a, &b) == 1);
    CU_ASSERT(projected_path.list[0].lon == 162);
    CU_ASSERT(projected_path.list[0].lat == 162);
    CU_ASSERT(projected_path.list[1].lon == 162);
    CU_ASSERT(projected_path.list[1].lat == 270);
    CU_ASSERT(projected_path.list[2].lon == 270);
    CU_ASSERT(projected_path.list[2].lat == 270);
    CU_ASSERT(projected_path.list[3].lon == 378);
    CU_ASSERT(projected_path.list[3].lat == 270);
    CU_ASSERT(projected_path.list[4].lon == 486);
    CU_ASSERT(projected_path.list[4].lat == 378);
    CU_ASSERT(projected_path.list[5].lon == 594);
    CU_ASSERT(projected_path.list[5].lat == 486);
    CU_ASSERT(projected_path.list[6].lon == 702);
    CU_ASSERT(projected_path.list[6].lat == 594);
    CU_ASSERT(projected_path.list[7].lon == 810);
    CU_ASSERT(projected_path.list[7].lat == 594);
    CU_ASSERT(projected_path.list[8].lon == 918);
    CU_ASSERT(projected_path.list[8].lat == 594);
    CU_ASSERT(projected_path.list[9].lon == 1026);
    CU_ASSERT(projected_path.list[9].lat == 594);
}

void test_astar_2() {
    position a, b;
    position_list projected_path;
        
    a.x = 1;
    a.y = 1;
    b.x = 10;
    b.y = 5;    
    projected_path = indoor_astar(&a, &b);
    
    CU_ASSERT(selected_tiles_are_valid_for_astar(&a, &b) == 0);
}