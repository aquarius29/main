#include "../../src/indoor/path_structure.h"

void test_indoor_navigation_1() {
    position a, b;
    
    a.x = 1;
    a.y = 1;
    b.x = 3;
    b.y = 3;
    
    init_path(a, b);
}

// void test_indoor_navigation_2() {
//     position a, b;
//     
//     a.x = 1;
//     a.y = 1;
//     b.x = 2;
//     b.y = 2;
//     
//     init_path(a, b);
//     
//     struct timeval t;
//     
// 
//     (void) time(&t);
//     
//     collision_avoided(0, t);
// }