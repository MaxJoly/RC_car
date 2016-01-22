#include "ros/ros.h"
#include "std_msgs/String.h"
#include "../include/VABB/BlackLib/v3_0/BlackLib.h"
#include "defines.h"
#include "VABB/Command.h"
#include "VABB/RSRMsg.h"

BlackLib::BlackPWM pwmServomotor(BlackLib::P8_13);

void refreshPWM_servomotor(const VABB::CommandConstPtr& cmd)
{
  float dirCoef = 0.0;

  ROS_INFO("iServomotor received from tCommand: %f", cmd->dir);

  // Mise à jour du temps haut (en us) en fonction de dir
  dirCoef = (DIR_COEF_MAX - DIR_COEF_MIN)/(SERVOMOTOR_ANGLE_MAX - SERVOMOTOR_ANGLE_MIN)*(cmd->dir) + 0.5*(DIR_COEF_MAX + DIR_COEF_MIN);
  pwmServomotor.setLoadRatioTime(round(1000000/PWM_SERVOMOTOR_FREQ*dirCoef), BlackLib::microsecond);
}

void RSR_process(const VABB::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iServomotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    pwmServomotor.setRunState(BlackLib::stop);
  }

  if(RSR->reset)
  {
    pwmServomotor.setRunState(BlackLib::stop);
    pwmServomotor.setLoadRatioTime(0, BlackLib::microsecond);
  }
}

int main(int argc, char **argv)
{
  // TODO : vérifier que les commandes ont répondu et envoyer un message à tError sinon
  pwmServomotor.setPeriodTime(PWM_SERVOMOTOR_FREQ, BlackLib::microsecond);
  pwmServomotor.setLoadRatioTime(0, BlackLib::microsecond);
  pwmServomotor.setPolarity(BlackLib::straight);
  pwmServomotor.setRunState(BlackLib::run);
  
  ros::init(argc, argv, "iServomotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_servomotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  ros::spin();

  return 0;
}
