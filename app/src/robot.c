#include "robot.h"

#include "robot_tasks.h"
#include "chassis_task.h"
#include "remote.h"
#include "bsp_can.h"

void Robot_Init() {
    // Initialize all hardware
    Chassis_Task_Init();
    Remote_Init();
    CAN_Service_Init();
    // Initialize all tasks
    Robot_Tasks_Start();
}

void Robot_Ctrl_Loop() {
    // Control loop for the robot
    Chassis_Ctrl_Loop();
}