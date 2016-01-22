#include "pwm.h"
#include <stdio.h>
#include <stdlib.h>

PWM::PWM(std::string directory_path)
{
	this->directory=directory_path;
	this->setDuty(0);
	this->setPeriod(14000000);
	this->setPolarity(true);
	this->setRunningState(true);
}

PWM::PWM(std::string directory_path, int duty)
{
	this->directory=directory_path;
	this->setDuty(duty);
	this->setPeriod(14000000);
	this->setPolarity(true);
	this->setRunningState(true);
}

PWM::PWM(std::string directory_path, int duty, int period)
{
	this->directory=directory_path;
	this->setDuty(duty);
	this->setPeriod(period);
	this->setPolarity(true);
	this->setRunningState(true);
}

PWM::PWM(std::string directory_path, int duty, int period, bool polarity)
{
	this->directory=directory_path;
	this->setDuty(duty);
	this->setPeriod(period);
	this->setPolarity(polarity);
	this->setRunningState(true);
}

PWM::PWM(std::string directory_path, int duty, int period, bool polarity, bool enable)
{
	this->directory=directory_path;
	this->setDuty(duty);
	this->setPeriod(period);
	this->setPolarity(polarity);
	this->setRunningState(enable);
}

void PWM::setPeriod(int period)
{
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/period", "w");

	if(f==NULL)
	{
		printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/period\n");
	}
	else
	{
		fprintf(f, "%d", period);
		fclose(f);
	}
}

void PWM::setDuty(int duty)
{
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/duty_cycle", "w");

	if(f==NULL)
	{
		 printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/duty_cycle\n");
	}
	else
	{
		fprintf(f, "%d", duty);
		fclose(f);
	}
}

void PWM::setPolarity(bool polarity)
{
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/polarity", "w");

	if(f==NULL)
	{
		 printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/polarity\n");
	}
	else
	{
		fprintf(f, "%d", polarity?1:0);
		fclose(f);
	}
}

void PWM::setRunningState(bool enable)
{
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/enable", "w");

	if(f==NULL)
	{
		 printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/enable\n");
	}
	else
	{
		fprintf(f, "%d", enable?1:0);
		fclose(f);
	}
}

int PWM::getPeriod(void)
{
	int period=0;
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/period", "r");

	if(f==NULL)
	{
		printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/period\n");
		return -1;
	}
	else
	{
		fscanf(f, "%d", period);
		fclose(f);
		return period;
	}
}

int PWM::getDuty(void)
{
	int duty=0;
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/duty_cycle", "r");

	if(f==NULL)
	{
		printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/duty_cycle\n");
		return -1;
	}
	else
	{
		fscanf(f, "%d", duty);
		fclose(f);
		return duty;
	}
}

bool PWM::isPolarityStraight(void)
{
	int polarity=0;
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/polarity", "r");

	if(f==NULL)
	{
		printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/polarity\n");
		return -1;
	}
	else
	{
		fscanf(f, "%d", polarity);
		fclose(f);
		return polarity?true:false;
	}
}

bool PWM::isEnabled(void)
{
	int enabled=0;
	FILE* f=fopen("/sys/class/pwm/" + this->directory + "/enable", "r");

	if(f==NULL)
	{
		printf("\nImpossible d'ouvrir le fichier " + "/sys/class/pwm/" + this->directory + "/enable\n");
		return -1;
	}
	else
	{
		fscanf(f, "%d", enabled);
		fclose(f);
		return enabled?true:false;
	}
}
