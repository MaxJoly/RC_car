#include "ros/ros.h"
#include "std_msgs/String.h"
#include "defines.h"
#include "rc_car/Command.h"
#include "rc_car/RSRMsg.h"
#include "rc_car/pwm.h"

PWM pwmDCmotor(PWM_DC_MOTOR_DIR, 0, PWM_DC_MOTOR_PERIOD_NS, true, false);

void refreshPWM_DCmotor(const rc_car::CommandConstPtr& cmd)
{
  float speedCoef = 0.0;

  ROS_INFO("iDCmotor received from tCommand: %f", cmd->speed);

  // Mise à jour du temps haut (en us) en fonction de speed
  speedCoef = (SPEED_COEF_MAX - SPEED_COEF_MIN)/(DC_MOTOR_SPEED_MAX - DC_MOTOR_SPEED_MIN)*(cmd->speed) + 0.5*(SPEED_COEF_MAX + SPEED_COEF_MIN);
  pwmDCmotor.setDuty(round(PWM_DC_MOTOR_PERIOD_NS*speedCoef));
}

void RSR_process(const rc_car::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iDCmotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    pwmDCmotor.setRunningState(false);
  }

  if(RSR->reset)
  {
    pwmDCmotor.setRunningState(false);
    pwmDCmotor.setDuty(0);
  }
}

int main(int argc, char **argv)
{
  // TODO : vérifier que les commandes ont répondu et envoyer un message à tError sinon

  ros::init(argc, argv, "iDCmotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_DCmotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  ros::spin();

  return 0;
}
