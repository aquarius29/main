/*!
 * @file cunit_master_test_suite.h 
 * @brief   Header file for prototyping all test functions.
 * @date 2011-04-28
 * @author Any one from Motor Controll group that has written a cunit test.
 * @version 1.1
 * @history 2011-05-18 - Restructured and added comments (Kristofer)
            2011-04-28 - file created \n
 * @details A header file for prototyping all test functions from the \n
            different cunit test modules so that they can be compiled \n
            into one big test file.
 */

/* -----------------------------------------------------------
 * Test cases defined in cunit_moto_interface.c
 * (Can be compiled separately with 
 * gcc -DPC -DAUTOMATED test/cunit_moto_interface.c test/cunit_master_test_suite.h src/*.c ../proto_mega/src/*.c -o bin/q.o -lcunit
 *
 *  -----------------------------------------------------------
 */

/* Björns test cases */ 
void test_moto_init(void);
/* -----------------------------------------------------------
 * Test cases defined in cunit_moto_msg_handler.c
 * (Can be compiled separately with 
 * gcc -DPC -DAUTOMATED test/cunit_moto_msg_handler.c test/cunit_master_test_suite.h src/*.c ../proto_mega/src/*.c -o bin/q.o -lcunit
 *
 *  -----------------------------------------------------------
 */

/* Björns test cases */ 
void test_moto_specialMotorCommand(void);
void test_moto_controlMotors(void);

/* Kristofers test cases */ 
void test_moto_examineID(void);
void test_moto_examineID_bad_msg(void);

/* Rahwas test cases */ 
void test_examineID_start(void);
void examineID_controlMotors(void);
void examineID_specialCommands(void);
void test_examineID_stop(void);

/* -----------------------------------------------------------
 * Test cases defined in cunit_moto_driver_functions.c
 * (Can be compiled separately with 
 * gcc -DPC -DAUTOMATED test/cunit_moto_driver_functions.c test/cunit_master_test_suite.h src/*.c ../proto_mega/src/*.c -o bin/q.o -lcunit
 *
 *  -----------------------------------------------------------
 */

/* Björns test cases defined in cunit_moto_driver_functions */
void test_moto_specialCommands(void);

/* Bishares test cases defined in cunit_moto_driver_functions */
void test_moto_startMotors(void);
void test_moto_stopMotors(void);
void test_moto_increaseAllNormal(void);
void test_moto_decreaseAllNormal(void);
void test_moto_increaseAllPanic(void);
void test_moto_decreaseAllPanic(void);
void test_moto_hover(void);
void test_moto_goForward(void);
void test_moto_goBackward(void);
void test_moto_strafeRight(void);
void test_moto_strafeLeft(void);
void test_moto_rotateLeft(void);
void test_moto_rotateRight(void);

