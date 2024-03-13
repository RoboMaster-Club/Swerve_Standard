#include "gimbal_task.h"
#include "dji_motor.h"
#include "robot.h"
#include "remote.h"
#include "imu_task.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
extern IMU_t g_imu;
DJI_Motor_Handle_t *g_yaw, *g_pitch;
Gimbal_Target_t g_gimbal_target;

void Gimbal_Task_Init() {
    Motor_Config_t yaw_motor_config = {
        .can_bus = 1,
        .speed_controller_id = 5,
        .offset = 0,
        .control_mode = VELOCITY_CONTROL,
        .reversal = MOTOR_REVERSAL_NORMAL,
        .velocity_pid =
            {
                .kp = 500.0f,
                .output_limit = GM6020_MAX_CURRENT,
            },
    };

    Motor_Config_t pitch_motor_config = {
        .can_bus = 1,
        .speed_controller_id = 6,
        .offset = 0,
        .control_mode = POSITION_CONTROL,
        .reversal = MOTOR_REVERSAL_NORMAL,
        .angle_pid =
            {
                .kp = 20000.0f,
                .ki = 1.2f,
                .output_limit = GM6020_MAX_CURRENT,
                .integral_limit = 1000.0f,
            }
    };

    g_yaw = DJI_Motor_Init(&yaw_motor_config,GM6020);
    g_pitch = DJI_Motor_Init(&pitch_motor_config,GM6020);
}

void Gimbal_Ctrl_Loop() {
    if (g_robot_state.enabled) {
       
       g_gimbal_target.pitch += g_remote.controller.right_stick.y/1000.0f;
       g_gimbal_target.yaw_velocity = g_remote.controller.right_stick.x/22.0f;

       DJI_Motor_Set_Angle(g_yaw,g_gimbal_target.pitch);
       DJI_Motor_Set_Velocity(g_pitch,g_gimbal_target.yaw_velocity);
    } else {
        DJI_Motor_Disable(g_yaw);
        DJI_Motor_Disable(g_pitch);
    }
}
