#include "ros/ros.h"
#include "std_msgs/String.h"
#include "defines.h"
#include "rc_car/CalibMsg.h"
#include "rc_car/Command.h"
#include "rc_car/RSRMsg.h"
#include "pwm.h"

PWM pwmDCmotor(PWM_DC_MOTOR_DIR, 0, PWM_DC_MOTOR_PERIOD_NS, true, false);
int DCmotor_period_speed_max = 0;
int DCmotor_period_speed_0 = 0;
int DCmotor_period_speed_min = 0;
int DCmotor_speed_max = 0;
int DCmotor_speed_min = 0;

/*
void refresh_param_DCmotor(const rc_car::CalibMsgConstPtr& calib)
{
  ROS_INFO("iDCmotor received from tCalib:\nDCmotor_period_speed_max: %d\tDCmotor_period_speed_0: %d\tDCmotor_period_speed_min: %d\tDCmotor_speed_max: %d\tDCmotor_speed_min: %d\n", calib->DCmotor_period_speed_max, calib->DCmotor_period_speed_0, calib->DCmotor_period_speed_min, calib->DCmotor_speed_max, calib->DCmotor_speed_min);

  DCmotor_period_speed_max = calib->DCmotor_period_speed_max;
  DCmotor_period_speed_0 = calib->DCmotor_period_speed_0;
  DCmotor_period_speed_min = calib->DCmotor_period_speed_min;
  DCmotor_speed_max = calib->DCmotor_speed_max;
  DCmotor_speed_min = calib->DCmotor_speed_min;
}
*/

void refreshPWM_DCmotor(const rc_car::CommandConstPtr& cmd)
{
  float dutyPeriod = 0.0;

  ROS_INFO("iDCmotor received from tCommand: %f", cmd->speed);

  // Mise à jour du temps haut (en ns) en fonction de speed
  dutyPeriod = (DCmotor_period_speed_max - DCmotor_period_speed_min)/(DCmotor_speed_max - DCmotor_speed_min)*(cmd->speed) + DCmotor_period_speed_0;
  pwmDCmotor.setDuty(round(dutyPeriod));
}

void RSR_process(const rc_car::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iDCmotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    pwmDCmotor.setRunningState(false);
  }
  else
  {
    pwmDCmotor.setRunningState(true);
  }

  if(RSR->reset)
  {
    pwmDCmotor.setDuty(0);
  }
}

int main(int argc, char **argv)
{
  // TODO : vérifier que les commandes ont répondu et envoyer un message à tError sinon
  std::string s;
  
  ros::init(argc, argv, "iDCmotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_DCmotor);
  //ros::Subscriber tCalib_sub = n.subscribe("tCalib", 1000, refresh_param_DCmotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  if (n.getParam("DCmotor_period_speed_max", s))
  {
    ROS_INFO("iDCmotor got param: %s\n", s.c_str());
    DCmotor_period_speed_max = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_period_speed_max'\n");
  }

  if (n.getParam("DCmotor_period_speed_0", s))
  {
    ROS_INFO("iDCmotor got param: %s\n", s.c_str());
    DCmotor_period_speed_0 = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_period_speed_0'\n");
  }

  if (n.getParam("DCmotor_period_speed_min", s))
  {
    ROS_INFO("iDCmotor got param: %s\n", s.c_str());
    DCmotor_period_speed_min = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_period_speed_min'\n");
  }

  if (n.getParam("DCmotor_speed_max", s))
  {
    ROS_INFO("iDCmotor got param: %s\n", s.c_str());
    DCmotor_speed_max = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_speed_max'\n");
  }

  if (n.getParam("DCmotor_speed_min", s))
  {
    ROS_INFO("iDCmotor got param: %s\n", s.c_str());
    DCmotor_speed_min = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_speed_min'\n");
  }

  ros::spin();

  return 0;
}