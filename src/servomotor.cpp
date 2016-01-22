#include "ros/ros.h"
#include "std_msgs/String.h"
#include "defines.h"
#include "rc_car/Command.h"
#include "rc_car/RSRMsg.h"
#include "pwm.h"

PWM pwmServomotor(PWM_SERVOMOTOR_DIR, 0, PWM_SERVOMOTOR_PERIOD_NS, true, false);

void refreshPWM_Servomotor(const rc_car::CommandConstPtr& cmd)
{
  float dirCoef = 0.0;

  ROS_INFO("iServomotor received from tCommand: %f", cmd->dir);

  // Mise à jour du temps haut (en us) en fonction de speed
  dirCoef = (DIR_COEF_MAX - DIR_COEF_MIN)/(SERVOMOTOR_ANGLE_MAX - SERVOMOTOR_ANGLE_MIN)*(cmd->dir) + 0.5*(DIR_COEF_MAX + DIR_COEF_MIN);
  pwmServomotor.setDuty(round(PWM_SERVOMOTOR_PERIOD_NS*dirCoef));
}

void RSR_process(const rc_car::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iServomotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    pwmServomotor.setRunningState(false);
  }

  if(RSR->reset)
  {
    pwmServomotor.setRunningState(false);
    pwmServomotor.setDuty(0);
  }
}

int main(int argc, char **argv)
{
  // TODO : vérifier que les commandes ont répondu et envoyer un message à tError sinon
  
  ros::init(argc, argv, "iServomotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_Servomotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  ros::spin();

  return 0;
}