#include "robot.h"

#include "robot_tasks.h"
#include "chassis_task.h"
#include "bsp_can.h"

void Robot_Init() {
    // Initialize all hardware
    Chassis_Init();
    CAN_Service_Init();
    // Initialize all tasks
    Robot_Tasks_Start();
}
