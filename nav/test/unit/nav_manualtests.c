#include "../../src/nav_handlemanualcommands.h"

void test_manual_1() {
    initManualCommandsList();
    CU_ASSERT(first == 0);
    CU_ASSERT(last == 0);
}

void test_manual_2(void)
{
    receiveManualMovementCommand(3);
    
    CU_ASSERT(first->value == 3);
    CU_ASSERT(last->value == 3);
    CU_ASSERT(first->next == 0);    
    CU_ASSERT(last->next == 0);
    CU_ASSERT(first == last);
}

void test_manual_3(void)
{
    receiveManualMovementCommand(2);
    
    CU_ASSERT(first->value == 3);
    CU_ASSERT(first->next->value == 2);
    CU_ASSERT(last->value == 2);
    CU_ASSERT(last->next == 0);
    CU_ASSERT(first->next == last);
}