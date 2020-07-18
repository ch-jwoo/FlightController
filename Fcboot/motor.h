#ifndef __MOTOR_H
#define __MOTOR_H

#define MOTOR_PWM_MIN 1000
#define MOTOR_PWM_MAX 2000

struct motor{
	TIM_HandleTypeDef* pTim;
	uint32_t Channel;
	uint16_t pwm;
};


void motor_init(struct motor *m, TIM_HandleTypeDef *htim, uint32_t Channel){
	m->pTim = htim;
	m->Channel = Channel;
	m->pwm = MOTOR_PWM_MIN;
}

void motor_write(struct motor *m, uint16_t pwm){
	if(pwm < MOTOR_PWM_MIN) pwm = MOTOR_PWM_MIN;
	else if(pwm > MOTOR_PWM_MAX) pwm = MOTOR_PWM_MAX;
	m->pwm = pwm;

	pwm *= 2; // scale the signal for time
	__HAL_TIM_SET_COMPARE(m->pTim, m->Channel, pwm);
}
void motor_start(struct motor *m){
    HAL_TIM_PWM_Start(m->pTim, m->Channel);
    motor_write(m, m->pwm);
}


void motor_deinit(struct motor *m){
	HAL_TIM_PWM_Stop(m->pTim, m->Channel);
	m->pwm = MOTOR_PWM_MIN;
}

struct motor iMotor1;
struct motor iMotor2;
struct motor iMotor3;
struct motor iMotor4;
struct motor iMotor5;
struct motor iMotor6;

#endif
