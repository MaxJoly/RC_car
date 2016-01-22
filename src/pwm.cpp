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
	std::string filepath = "/sys/class/pwm/" + this->directory + "/period";
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "w");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
	}
	else
	{
		fprintf(f, "%d", period);
		fclose(f);
	}
}

void PWM::setDuty(int duty)
{
	std::string filepath = "/sys/class/pwm/" + this->directory + "/duty_cycle";
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "w");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
	}
	else
	{
		fprintf(f, "%d", duty);
		fclose(f);
	}
}

void PWM::setPolarity(bool polarity)
{
	std::string filepath = "/sys/class/pwm/" + this->directory + "/polarity";
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "w");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
	}
	else
	{
		fprintf(f, "%d", polarity?1:0);
		fclose(f);
	}
}

void PWM::setRunningState(bool enable)
{
	std::string filepath = "/sys/class/pwm/" + this->directory + "/enable";
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "w");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
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
	std::string filepath = "/sys/class/pwm/" + this->directory + "/period";
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
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
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
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
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
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
	std::string errormsg = "\nImpossible d'ouvrir le fichier " + filepath + "\n";
	FILE* f=fopen(filepath.c_str(), "r");

	if(f==NULL)
	{
		//printf(errormsg.c_str());
		return -1;
	}
	else
	{
		fscanf(f, "%d", &enabled);
		fclose(f);
		return (enabled==1)?true:false;
	}
}
