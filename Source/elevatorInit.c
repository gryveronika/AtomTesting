#include "elevatorInit.h"

void initElevatorFloor() {
  hardware_command_movement(HARDWARE_ORDER_DOWN);
  while (hardware_read_floor_sensor(0) != 1) {
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
      if (hardware_read_floor_sensor(i)) {
          hardware_command_floor_indicator_on(i);
        }
      }
  }
  hardware_command_floor_indicator_on(0);
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void initElevator() {
  initElevatorFloor();
}
