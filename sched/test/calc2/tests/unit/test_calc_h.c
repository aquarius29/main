#include "../../src/calc.h"

CalcStatePtr calc = NULL;

/* Set up and clean up test suite */

int init_suite(void) {
  calc = mkCalcState();
  return calc == NULL;
}

int clean_suite(void) {
  freeCalcState(calc);
  calc=NULL;
  return 0;
}

void testCase1(void) {
  // Enter 17+3=, monitor buffer between button presses

  // Initial buffer is empty
  CU_ASSERT(!strcmp(getBuffer(calc), ""));

  // Press '1'  (expected buffer: "1")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "1"));

  // Press '7'  (expected buffer: "17")
  pressDigit(calc, '7');
  CU_ASSERT(!strcmp(getBuffer(calc), "17"));
  
  // Press '+'  (expected buffer: "17")
  pressPlus(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "17"));

  // Press '3'  (expected buffer: "3")
  pressDigit(calc, '3');
  CU_ASSERT(!strcmp(getBuffer(calc), "3"));

  // Press '='  (expected buffer: "20")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "20"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}

void testCase2(void) {
  // Enter 56-41=, monitor buffer between button presses

	// Press '5' (expected buffer: "5")
	pressDigit(calc, '5');
	CU_ASSERT(!strcmp(getBuffer(calc), "5"));

 	// Press '6' (expected buffer: "56")
	pressDigit(calc, '6');
	CU_ASSERT(!strcmp(getBuffer(calc), "56"));

	// Press '-'  (expected buffer: "56")
  pressMinus(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "56"));

	// Press '4'  (expected buffer: "4")
  pressDigit(calc, '4');
  CU_ASSERT(!strcmp(getBuffer(calc), "4"));

	// Press '1'  (expected buffer: "41")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "41"));

	// Press '='  (expected buffer: "15")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "15"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}


void testCase3(void){
 // Enter 12*234 =, monitor buffer between button presses

	// Press '1' (expected buffer: "1")
	pressDigit(calc, '1');
	CU_ASSERT(!strcmp(getBuffer(calc), "1"));

 	// Press '2' (expected buffer: "12")
	pressDigit(calc, '2');
	CU_ASSERT(!strcmp(getBuffer(calc), "12"));

	// Press '*'  (expected buffer: "12")
  pressMult(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "12"));

	// Press '2'  (expected buffer: "2")
  pressDigit(calc, '2');
  CU_ASSERT(!strcmp(getBuffer(calc), "2"));

	// Press '3'  (expected buffer: "23")
  pressDigit(calc, '3');
  CU_ASSERT(!strcmp(getBuffer(calc), "23"));

	// Press '4'  (expected buffer: "234")
  pressDigit(calc, '4');
  CU_ASSERT(!strcmp(getBuffer(calc), "234"));

	// Press '='  (expected buffer: "2808")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "2808"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}

void testCase4(void) {
  // Enter 35/5 = , monitor buffer between button presses

  // Press '3'  (expected buffer: "3")
  pressDigit(calc, '3');
  CU_ASSERT(!strcmp(getBuffer(calc), "3"));

  // Press '5'  (expected buffer: "35")
  pressDigit(calc, '5');
  CU_ASSERT(!strcmp(getBuffer(calc), "35"));
  
  // Press '/'  (expected buffer: "35")
  pressDiv(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "35"));

  // Press '5'  (expected buffer: "5")
  pressDigit(calc, '5');
  CU_ASSERT(!strcmp(getBuffer(calc), "5"));

  // Press '='  (expected buffer: "7")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "7"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));

}

void testCase5(void) {
	// Test reset button

	// Press 'C' (expected buffer "")
	pressReset(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), ""));

	 // Press '9'  (expected buffer: "9")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "9"));

	// Press 'C' (expected buffer "")
	pressReset(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), ""));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}


void testCase6(void) {
  // Enter 3 + + , acoording to specification, the second operation "+" will be considered as "=", and oprand is "3", digit in buffer is "3",
  // so that the result of this caculation should be 6. 

	// Press '3'  (expected buffer: "3")
  pressDigit(calc, '3');
  CU_ASSERT(!strcmp(getBuffer(calc), "3"));

  // Press '+'  (expected buffer: "3")
  pressPlus(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "3"));
  
  // Press '+'  (expected buffer: "6")
  pressPlus(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "6"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}

void testCase7(void) {
	//  Test the bundary of number(The maximum is 15 digit), if the number out of boundary, there will be a error on buffer.
 
  // Press '1'  (expected buffer: "1")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "1"));

	// Press '2'  (expected buffer: "12")
  pressDigit(calc, '2');
  CU_ASSERT(!strcmp(getBuffer(calc), "12"));

  // Press '3'  (expected buffer: "123")
  pressDigit(calc, '3');
  CU_ASSERT(!strcmp(getBuffer(calc), "123"));

	// Press '4'  (expected buffer: "1234")
  pressDigit(calc, '4');
  CU_ASSERT(!strcmp(getBuffer(calc), "1234"));

	// Press '5'  (expected buffer: "12345")
  pressDigit(calc, '5');
  CU_ASSERT(!strcmp(getBuffer(calc), "12345"));

	// Press '6'  (expected buffer: "123456")
  pressDigit(calc, '6');
  CU_ASSERT(!strcmp(getBuffer(calc), "123456"));

  // Press '7'  (expected buffer: "1234567")
  pressDigit(calc, '7');
  CU_ASSERT(!strcmp(getBuffer(calc), "1234567"));

	// Press '8'  (expected buffer: "12345678")
  pressDigit(calc, '8');
  CU_ASSERT(!strcmp(getBuffer(calc), "12345678"));

	// Press '9'  (expected buffer: "123456789")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "123456789"));

	// Press '1'  (expected buffer: "1234567891")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "1234567891"));

	// Press '2'  (expected buffer: "12345678912")
  pressDigit(calc, '2');
  CU_ASSERT(!strcmp(getBuffer(calc), "12345678912"));

	// Press '3'  (expected buffer: "123456789123")
  pressDigit(calc, '3');
  CU_ASSERT(!strcmp(getBuffer(calc), "123456789123"));

	// Press '4'  (expected buffer: "1234567891234")
  pressDigit(calc, '4');
  CU_ASSERT(!strcmp(getBuffer(calc), "1234567891234"));

	// Press '5'  (expected buffer: "12345678912345")
  pressDigit(calc, '5');
  CU_ASSERT(!strcmp(getBuffer(calc), "12345678912345"));

	// Press '6'  (expected buffer: "123456789123456")
  pressDigit(calc, '6');
  CU_ASSERT(!strcmp(getBuffer(calc), "123456789123456"));

	// Press '7'  (expected buffer: "[error]")
  pressDigit(calc, '7');
  CU_ASSERT(!strcmp(getBuffer(calc), "[error]"));

	// Press '1'  (expected buffer: "[error]")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "[error]"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}



void testCase8(void) {		
	// Enter 	9-1+7 =   Test mutiple operation.
 
	// Press '9'  (expected buffer: "9")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "9"));

	// Press '-'  (expected buffer: "9")
  pressMinus(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "9"));

	// Press '1'  (expected buffer: "1")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "1"));

	// Press '+'  (expected buffer: "8")
  pressPlus(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "8"));

	// Press '7'  (expected buffer: "7")
  pressDigit(calc, '7');
  CU_ASSERT(!strcmp(getBuffer(calc), "7"));

	// Press '='  (expected buffer: "15")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "15"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}

void testCase9(void) {
	// Enter 23 -10 = = =  Test if execute button '=' press more than one time, the result would not be changed, and no errors. 

	// Press '2'  (expected buffer: "2")
  pressDigit(calc, '2');
  CU_ASSERT(!strcmp(getBuffer(calc), "2"));

	// Press '3'  (expected buffer: "23")
  pressDigit(calc, '3');
  CU_ASSERT(!strcmp(getBuffer(calc), "23"));

	// Press '-'  (expected buffer: "23")
  pressMinus(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "23"));

	// Press '1'  (expected buffer: "1")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "1"));

	// Press '0'  (expected buffer: "10")
  pressDigit(calc, '0');
  CU_ASSERT(!strcmp(getBuffer(calc), "10"));

	// Press '='  (expected buffer: "13")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "13"));

	// Press '='  (expected buffer: "13")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "13"));

  // Press '='  (expected buffer: "13")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "13"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}

void testCase10(void) {
	// Enter 99999999999*1000000 =  two numbers are in boundary, but the result will be out out boundary(15 digits)
  // The last buffer should display [error] if the result out of boundary. 

	// Press '9'  (expected buffer: "9")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "9"));

	// Press '9'  (expected buffer: "99")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "99"));

	// Press '9'  (expected buffer: "999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "999"));
	
	// Press '9'  (expected buffer: "9999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "9999"));

	// Press '9'  (expected buffer: "99999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "99999"));

	// Press '9'  (expected buffer: "999999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "999999"));

	// Press '9'  (expected buffer: "9999999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "9999999"));

	// Press '9'  (expected buffer: "99999999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "99999999"));

	// Press '9'  (expected buffer: "999999999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "999999999"));

	// Press '9'  (expected buffer: "9999999999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "9999999999"));

	// Press '9'  (expected buffer: "99999999999")
  pressDigit(calc, '9');
  CU_ASSERT(!strcmp(getBuffer(calc), "99999999999"));

	// Press '*'  (expected buffer: "99999999999")
  pressMult(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "99999999999"));
	
	// Press '1'  (expected buffer: "1")
  pressDigit(calc, '1');
  CU_ASSERT(!strcmp(getBuffer(calc), "1"));

	// Press '0'  (expected buffer: "0")
  pressDigit(calc, '0');
  CU_ASSERT(!strcmp(getBuffer(calc), "10"));

	// Press '0'  (expected buffer: "0")
  pressDigit(calc, '0');
  CU_ASSERT(!strcmp(getBuffer(calc), "100"));

	// Press '0'  (expected buffer: "0")
  pressDigit(calc, '0');
  CU_ASSERT(!strcmp(getBuffer(calc), "1000"));

	// Press '0'  (expected buffer: "0")
  pressDigit(calc, '0');
  CU_ASSERT(!strcmp(getBuffer(calc), "10000"));

	// Press '0'  (expected buffer: "0")
  pressDigit(calc, '0');
  CU_ASSERT(!strcmp(getBuffer(calc), "100000"));

 // Press '='  (expected buffer: "[error]")
  pressExec(calc);
  CU_ASSERT(!strcmp(getBuffer(calc), "[error]"));
	
	pressReset(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
}

void testCase11(void){
	//Test to make the operand negative
	pressMinus(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
	
	pressDigit(calc, '1');
	CU_ASSERT(!strcmp(getBuffer(calc), "1"));
	
	pressMinus(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), "-1"));
	
	pressMinus(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), "-1"));
	
	pressDigit(calc, '4');
	CU_ASSERT(!strcmp(getBuffer(calc), "4"));
	
	pressExec(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), "-5"));
}

void testCase12(void){
	//Test to put the calc state to error
	pressMinus(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
	
	pressDigit(calc, '0');
	CU_ASSERT(!strcmp(getBuffer(calc), "0"));
	
	pressDiv(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), ""));
	
	pressDigit(calc, '0');
	CU_ASSERT(!strcmp(getBuffer(calc), "0"));
	
	pressMinus(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), "-1"));
	
	pressMinus(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), "-1"));
	
	pressDigit(calc, '0');
	CU_ASSERT(!strcmp(getBuffer(calc), "0"));
	
	pressExec(calc);
	CU_ASSERT(!strcmp(getBuffer(calc), "-5"));
}

