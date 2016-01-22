#include "pwm.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	PWM myPWM("pwmchip1/pwm1", 1000000, 10000000, 1, 1);

	printf("Duty: %d \t Period: %d \t Polarity: %d \t Enabled: %d \n", myPWM.getDuty(), myPWM.getPeriod(), myPWM.isPolarityStraight()?1:0, myPWM.isEnabled()?1:0);

	while(1)
	{
		sleep(500);
		myPWM.setDuty(5000000);
		printf("Duty: %d \t Period: %d \t Polarity: %d \t Enabled: %d \n", myPWM.getDuty(), myPWM.getPeriod(), myPWM.isPolarityStraight()?1:0, myPWM.isEnabled()?1:0);
		sleep(500);
		myPWM.setPeriod(20000000);
		printf("Duty: %d \t Period: %d \t Polarity: %d \t Enabled: %d \n", myPWM.getDuty(), myPWM.getPeriod(), myPWM.isPolarityStraight()?1:0, myPWM.isEnabled()?1:0);
		sleep(500);
		myPWM.setRunningState(false);
		printf("Duty: %d \t Period: %d \t Polarity: %d \t Enabled: %d \n", myPWM.getDuty(), myPWM.getPeriod(), myPWM.isPolarityStraight()?1:0, myPWM.isEnabled()?1:0);
	}
	return 0;
}