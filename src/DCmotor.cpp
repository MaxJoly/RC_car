#include "ros/ros.h"
#include "std_msgs/String.h"
#include "../include/VABB/BlackLib/v3_0/BlackLib.h"
#include "defines.h"
#include "VABB/Command.h"
#include "VABB/RSRMsg.h"

BlackLib::BlackPWM pwmDCmotor(BlackLib::P8_19);
// /sys/class/pwm/pwmchip1/pwm1/(polarity|period|duty_cycle)

void refreshPWM_DCmotor(const VABB::CommandConstPtr& cmd)
{
  float speedCoef = 0.0;

  ROS_INFO("iDCmotor received from tCommand: %f", cmd->speed);

  // Mise à jour du temps haut (en us) en fonction de speed
  speedCoef = (SPEED_COEF_MAX - SPEED_COEF_MIN)/(DC_MOTOR_SPEED_MAX - DC_MOTOR_SPEED_MIN)*(cmd->speed) + 0.5*(SPEED_COEF_MAX + SPEED_COEF_MIN);
  pwmDCmotor.setLoadRatioTime(round(1000000/PWM_DC_MOTOR_FREQ*speedCoef), BlackLib::microsecond);
}

void RSR_process(const VABB::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iDCmotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    pwmDCmotor.setRunState(BlackLib::stop);
  }

  if(RSR->reset)
  {
    pwmDCmotor.setRunState(BlackLib::stop);
    pwmDCmotor.setLoadRatioTime(0, BlackLib::microsecond);
  }
}

int main(int argc, char **argv)
{
  // TODO : vérifier que les commandes ont répondu et envoyer un message à tError sinon
  pwmDCmotor.setPeriodTime(PWM_DC_MOTOR_FREQ, BlackLib::microsecond);
  pwmDCmotor.setLoadRatioTime(0, BlackLib::microsecond);
  pwmDCmotor.setPolarity(BlackLib::straight);
  pwmDCmotor.setRunState(BlackLib::run);
  
  ros::init(argc, argv, "iDCmotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_DCmotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  ros::spin();

  return 0;
}