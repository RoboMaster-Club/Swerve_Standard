#include "chassis_task.h"

#include "dji_motor.h"

DJI_Motor_Handle_t *motor_lf, *motor_lr, *motor_rr, *motor_lr;

void Chassis_Init() {
    Motor_Config_t motor_config = {
        .can_bus = 1,
        .speed_controller_id = 3,
        .offset = 0,
        .reversal = MOTOR_REVERSAL_NORMAL,
        .control_mode = SPEED_CONTROL,
        .speed_pid = {
            .kp = 0,
            .ki = 0,
            .kd = 0,
            .integral_limit = 0,
            .output_limit = 0,
            .dead_zone = 0,
        },
    };
    motor_lf = DJI_Motor_Init(&motor_config, M3508);
}

void Chassis_Task() {

}