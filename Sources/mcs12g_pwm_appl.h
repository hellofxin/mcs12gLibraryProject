#ifndef MCS12G_PWM_APPL_H
#define MCS12G_PWM_APPL_H

unsigned char appl_pwm_init();
unsigned char appl_pwm_update();

unsigned char appl_pwm_setEnable(unsigned char enable);
unsigned char appl_pwm_setPolarity(unsigned char polarity);
unsigned char appl_pwm_setCenterAligned(unsigned char centerAligned);
unsigned char appl_pwm_setDutyPeriod(unsigned char channel, unsigned short duty, unsigned short period);

#endif