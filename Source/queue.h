#ifndef QUEUE_H
#define QUEUE_H

#include "utilities.h"
#include "hardware.h"
#include "Elevator.h"
/**
*@file
*/
/**
*@brief Sets index i in upQueue to 1 if there is a order to floor i.
*/

void addUpQueue(Elevator* elev);

/**
*@brief Sets index i in downQueue to 1 if there is a order to floor i.
*/

void addDownQueue(Elevator* elev);

/**
* @brief Returns 1 if the queue only has 0's
*
*/
int checkIfQueueEmpty(int queue[]);

/**

#endif
