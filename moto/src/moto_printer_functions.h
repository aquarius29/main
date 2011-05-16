 /*!@author Magnus Bergqvist,
 *          Kristofer Hansson Aspman
 *         
 * @file moto_printer_functions.h
 * @version v0.01
 * @date 2011-05-09
 *
 * @brief Contains macros for printing that is to be used for every file \n
 *        that needs a printout.
 *
 * @history 2011-05-09: Created the file. (Magnus & Kristofer)
 */

/* 
 * Printout macros inspired by Henrik Sandklef.
 * Will let the code result in different outputs (if any) depending
 * on what target it is compiled for.
 */

#ifdef ARDUINO
    #define PRINT_STRING(a)
    #define PRINT_DEC(a)
    #define PRINT_HEX(a)
    #define PRINT_NEW_LINE 
#elif defined ARDUINO_DBG
    #define PRINT_STRING(a) Serial.print(a)
    #define PRINT_DEC(a) Serial.print(a, DEC)
    #define PRINT_HEX(a) Serial.print(a, HEX)
    #define PRINT_NEW_LINE Serial.println()
#elif defined PC
    #define PRINT_STRING(a) printf(a)
    #define PRINT_DEC(a) printf("%d ", a)
    #define PRINT_HEX(a) printf("%x ", a)
    #define PRINT_NEW_LINE printf("\n")
#endif
