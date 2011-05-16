#include "../../src/nav_indoorstructure.h"

void test_indoor_navigation_1() {
    tile a, b;
    
    a.x = 1;
    a.y = 1;
    b.x = 2;
    b.y = 2;
    
    initPath(&a, &b);
}

// void test_indoor_navigation_2() {
//     position a, b;
//     
//     a.lat = 1;
//     a.lon = 1;
//     b.lat = 2;
//     b.lon = 2;
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