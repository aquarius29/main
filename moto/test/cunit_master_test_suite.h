/*!
 * @file cunit_master_test_suite.h 
 * @brief   Header file for prototyping all test functions.
 * @date 2011-04-28
 * @author Any one from Motor Controll group that has written a cunit test.
 * @version 1
 * @history 2011-04-28 - file created \n
 * @details A header file for prototyping all test functions from the \n
            different cunit test modules so that they can be compiled \n
            into one big test file.
 */
 
void test_moto_startMotors(void);
void test_moto_stopMotors(void);
void test_moto_increaseAllNormal(void);
void test_moto_decreaseAllNormal(void);
void test_moto_increaseAllPanic(void);
void test_moto_decreaseAllPanic(void);
void test_moto_specialMotorCommand(void);
void test_moto_controlMotors(void);

