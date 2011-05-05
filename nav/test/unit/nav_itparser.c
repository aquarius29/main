#include "../../src/tilemap.h"

void test_parse_xml() {
    ThreeDWorld map;
	fill_map(&map);
	
    CU_ASSERT(map.representation[0][0] == 1);
    CU_ASSERT(map.representation[1][1] == 0);
    CU_ASSERT(map.representation[2][3] == 0);
    CU_ASSERT(map.representation[3][7] == 1);
    CU_ASSERT(map.representation[5][1] == 0);
    CU_ASSERT(map.representation[10][5] == 1);
    CU_ASSERT(map.representation[11][9] == 1);
    // CU_ASSERT(map.representation[99][99] == NULL);
    
    // free(map.representation);
}