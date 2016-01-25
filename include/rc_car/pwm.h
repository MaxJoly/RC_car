#ifndef PWM_H_
#define PWM_H_
#include <string>

class PWM
{
private:
	std::string directory;

public:
	PWM(std::string directory_path);
	PWM(std::string directory_path, int duty);
	PWM(std::string directory_path, int duty, int period);
	PWM(std::string directory_path, int duty, int period, bool polarity);
	PWM(std::string directory_path, int duty, int period, bool polarity, bool enable);

	int getPeriod();
	int getDuty();
	bool isPolarityStraight();
	bool isEnabled();
	//Stream getInfo();

	void setPeriod(int period);
	void setDuty(int duty);
	void setPolarity(bool polarity);
	void setRunningState(bool enable);
};
#endif



