/** @file
*   @brief Various utility software
*
*/
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <time.h>
#include "hardware.h"
#include "stateMachine.h"


/** @brief Creates an delay for specified amount of seconds
*   @param[in] delay amount in seconds
*
*/
void delay_s(int seconds);

/**
 * @brief Finds the current floor (1,2,3,4)
 * @return the number of the etg as an int
 */
int currentFloor();

/**
 * @brief Counts down sec seconds
   @param[in] p_sec countdown in seconds
   @param[in] p_elev elevator which should be delayed
 * @return 1 when countdown is done
 */


#endif
