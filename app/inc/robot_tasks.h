#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


osThreadId imu_task_handle;
osThreadId robot_control_task_handle;
osThreadId motor_task_handle;
osThreadId ui_task_handle;

void Robot_Tasks_Robot_Control(void const *argument);
void Robot_Tasks_Motor(void const *argument);
void Robot_Tasks_IMU(void const *argument);

void Robot_Tasks_Start()
{
    osThreadDef(imu_task, Robot_Tasks_IMU, osPriorityAboveNormal, 0, 1024);
    imu_task_handle = osThreadCreate(osThread(imu_task), NULL);

    osThreadDef(motor_task, Robot_Tasks_IMU, osPriorityAboveNormal, 0, 256);
    motor_task_handle = osThreadCreate(osThread(motor_task), NULL);

    osThreadDef(robot_control_task, Robot_Tasks_Robot_Control, osPriorityAboveNormal, 0, 256);
    robot_control_task_handle = osThreadCreate(osThread(robot_control_task), NULL);

    osThreadDef(ui_task, Robot_Tasks_Robot_Control, osPriorityAboveNormal, 0, 256);
    ui_task_handle = osThreadCreate(osThread(ui_task), NULL);
}

void Robot_Tasks_Robot_Control(void const *argument)
{

}

__weak void Robot_Tasks_IMU(void const *argument)
{
    // Refer to bsp/device/imu_task.c
}

void Robot_Tasks_Motor(void const *argument)
{
    
}

void Robot_Tasks_UI(void const *argument)
{
    
}