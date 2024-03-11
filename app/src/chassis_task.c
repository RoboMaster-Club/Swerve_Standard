
#include "chassis_task.h"

#include "dji_motor.h"
#include "robot.h"
#include "remote.h"
#include "imu_task.h"

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
extern IMU_t g_imu;

DJI_Motor_Handle_t *motor_lf, *motor_rf, *motor_rr, *motor_lr;

void Chassis_Task_Init() {
    Motor_Config_t motor_config = {
        .can_bus = 1,
        .offset = 0,
        .reversal = MOTOR_REVERSAL_NORMAL,
        .control_mode = SPEED_CONTROL,
        .vel_unit_rpm = 1,
        .pos_abs_ctrl = 1,
        .speed_pid = {
            .kp = 500,
            .ki = 0,
            .kd = 0,
            .integral_limit = 5000,
            .output_limit = 16000,
            .dead_zone = 0,
        },
        .position_pid = {
            .kp = 15000,
            .ki = 1.2,
            .kd = 0,
            .integral_limit = 1000,
            .output_limit = 16000,
            .dead_zone = 0,
        },
    };

    motor_config.speed_controller_id = 1;
    motor_config.control_mode = POSITION_CONTROL;
    motor_rr = DJI_Motor_Init(&motor_config, GM6020);
}

void Chassis_Ctrl_Loop() {
    if (g_robot_state.enabled) {
        if (g_remote.controller.right_stick.x != 0 || g_remote.controller.right_stick.y != 0) {
            motor_rr->set_position(motor_rr, atan2(g_remote.controller.right_stick.y, g_remote.controller.right_stick.x));
        }
        // Control the robot
        // motor_lf->set_speed(motor_lf, g_remote.controller.right_stick.y);
        // motor_rf->set_speed(motor_rf, g_remote.controller.left_stick.y);
    } else {
        motor_rr->disable(motor_rr);
        // motor_lf->disable(motor_lf);
        // motor_rf->disable(motor_rf);
    }
}