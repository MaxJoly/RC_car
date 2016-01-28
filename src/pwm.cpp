#include "rc_car/pwm.h"
#include <stdio.h>
#include <stdlib.h>

PWM::PWM(std::string directory_path)
{
	this->directory=directory_path;
}

PWM::PWM(std::string directory_path, int duty)
{
	this->directory=directory_path;
	this->setDuty(duty);
}

PWM::PWM(std::string directory_path, int duty, int period)
{
	this->directory=directory_path;
	this->setDuty(duty);
	this->setPeriod(period);
}

PWM::PWM(std::string directory_path, int duty, int period, bool polarity)
{
	this->directory=directory_path;
	this->setDuty(duty);
	this->setPeriod(period);
	this->setPolarity(polarity);
}

PWM::PWM(std::string directory_path, int duty, int period, bool polarity, bool enable)
{
	this->directory=directory_path;
	this->setDuty(duty);
	this->setPeriod(period);
	this->setPolarity(polarity);
	this->setRunningState(enable);
}

bool PWM::setPeriod(int period)
{
	std::string filepath = "/sys/class/pwm/" + this->directory + "/period";
	FILE* f=fopen(filepath.c_str(), "w");

	if(period<=0)
		return false;

	if(f==NULL)
	{
		return false;
	}
	else
	{
		fprintf(f, "%d", period);
		fclose(f);
		return true;
	}
}

bool PWM::setDuty(int duty)
{
	std::string filepath = "/sys/class/pwm/" + this->directory + "/duty_cycle";
	FILE* f=fopen(filepath.c_str(), "w");

	if(duty<0)
		return false;

	if(f==NULL)
	{
		return false;
	}
	else
	{
		fprintf(f, "%d", duty);
		fclose(f);
		return true;
	}
}

bool PWM::setPolarity(bool polarity)
{
	std::string filepath = "/sys/class/pwm/" + this->directory + "/polarity";
	FILE* f=fopen(filepath.c_str(), "w");

	if(f==NULL)
	{
		return false;
	}
	else
	{
		fprintf(f, "%d", polarity?1:0);
		fclose(f);
		return true;
	}
}

bool PWM::setRunningState(bool enable)
{
	std::string filepath = "/sys/class/pwm/" + this->directory + "/enable";
	FILE* f=fopen(filepath.c_str(), "w");

	if(f==NULL)
	{
		return false;
	}
	else
	{
		fprintf(f, "%d", enable?1:0);
		fclose(f);
		return true;
	}
}

int PWM::getPeriod(void)
{
	int period=0;
	std::string filepath = "/sys/class/pwm/" + this->directory + "/period";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		return -1;
	}
	else
	{
		fscanf(f, "%d", &period);
		fclose(f);
		return period;
	}
}

int PWM::getDuty(void)
{
	int duty=0;
	std::string filepath = "/sys/class/pwm/" + this->directory + "/duty";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		return -1;
	}
	else
	{
		fscanf(f, "%d", &duty);
		fclose(f);
		return duty;
	}
}

bool PWM::isPolarityStraight(void)
{
	int polarity=0;
	std::string filepath = "/sys/class/pwm/" + this->directory + "/polarity";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		return -1;
	}
	else
	{
		fscanf(f, "%d", &polarity);
		fclose(f);
		return (polarity==1)?true:false;
	}
}

bool PWM::isEnabled(void)
{
	int enabled=0;
	std::string filepath = "/sys/class/pwm/" + this->directory + "/enable";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		return -1;
	}
	else
	{
		fscanf(f, "%d", &enabled);
		fclose(f);
		return (enabled==1)?true:false;
	}
}
