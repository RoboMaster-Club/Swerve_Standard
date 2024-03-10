
#include "chassis_task.h"

#include "dji_motor.h"

DJI_Motor_Handle_t *motor_lf, *motor_rf, *motor_rr, *motor_lr;

void Chassis_Task_Init() {
    Motor_Config_t motor_config = {
        .can_bus = 1,
        .offset = 0,
        .reversal = MOTOR_REVERSAL_NORMAL,
        .control_mode = SPEED_CONTROL,
        .vel_unit_rpm = 1,
        .pos_abs_ctrl = 0,
        .speed_pid = {
            .kp = 2000,
            .ki = 0,
            .kd = 0,
            .integral_limit = 0,
            .output_limit = 20000,
            .dead_zone = 0,
        },
    };
    motor_config.speed_controller_id = 1;
    motor_lf = DJI_Motor_Init(&motor_config, M2006);
    motor_config.speed_controller_id = 2;
    motor_rf = DJI_Motor_Init(&motor_config, M2006);
}

void Chassis_Ctrl_Loop() {
    motor_lf->set_speed(motor_lf, 1);
}