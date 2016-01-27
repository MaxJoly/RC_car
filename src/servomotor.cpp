#include "ros/ros.h"
#include "std_msgs/String.h"
#include "rc_car/defines.h"
#include "rc_car/CalibMsg.h"
#include "rc_car/Command.h"
#include "rc_car/RSRMsg.h"
#include "rc_car/pwm.h"

PWM pwmServomotor(PWM_SERVOMOTOR_DIR, 0, PWM_SERVOMOTOR_PERIOD_NS, true, false);
int servo_period_angle_max = 0;
int servo_period_angle_0 = 0;
int servo_period_angle_min = 0;
int servo_angle_max = 0;
int servo_angle_min = 0;

/*
void refresh_param_Servomotor(const rc_car::CalibMsgConstPtr& calib)
{
  ROS_INFO("iServomotor received from tCalib:\nservo_period_angle_max: %d\tservo_period_angle_0: %d\tservo_period_angle_min: %d\tservo_angle_max: %d\tservo_angle_min: %d\n", calib->servo_period_angle_max, calib->servo_period_angle_0, calib->servo_period_angle_min, calib->servo_angle_max, calib->servo_angle_min);

  servo_period_angle_max = calib->servo_period_angle_max;
  servo_period_angle_0 = calib->servo_period_angle_0;
  servo_period_angle_min = calib->servo_period_angle_min;
  servo_angle_max = calib->servo_angle_max;
  servo_angle_min = calib->servo_angle_min;
}
*/

void refreshPWM_Servomotor(const rc_car::CommandConstPtr& cmd)
{
  float dutyPeriod = 0.0;

  ROS_INFO("iServomotor received from tCommand: %f", cmd->dir);

  // Mise à jour du temps haut (en ns) en fonction de speed
  dutyPeriod = (servo_period_angle_max - servo_period_angle_min)/(servo_angle_max - servo_angle_min)*(cmd->dir) + servo_period_angle_0;
  pwmServomotor.setDuty(round(dutyPeriod));
}

void RSR_process(const rc_car::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iServomotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    pwmServomotor.setRunningState(false);
  }
  else
  {
    pwmServomotor.setRunningState(true);
  }

  if(RSR->reset)
  {
    pwmServomotor.setDuty(0);
  }
}

int main(int argc, char **argv)
{
  // TODO : vérifier que les commandes ont répondu et envoyer un message à tError sinon
  std::string s;

  ros::init(argc, argv, "iServomotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_Servomotor);
  //ros::Subscriber tCalib_sub = n.subscribe("tCalib", 1000, refresh_param_Servomotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  if (n.getParam("servo_period_angle_max", s))
  {
    ROS_INFO("iServomotor got param: %s\n", s.c_str());
    servo_period_angle_max = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_period_angle_max'\n");
  }

  if (n.getParam("servo_period_angle_0", s))
  {
    ROS_INFO("iServomotor got param: %s\n", s.c_str());
    servo_period_angle_0 = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_period_angle_0'\n");
  }

  if (n.getParam("servo_period_angle_min", s))
  {
    ROS_INFO("iServomotor got param: %s\n", s.c_str());
    servo_period_angle_min = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_period_angle_min'\n");
  }

  if (n.getParam("servo_angle_max", s))
  {
    ROS_INFO("iServomotor got param: %s\n", s.c_str());
    servo_angle_max = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_angle_max'\n");
  }

  if (n.getParam("servo_angle_min", s))
  {
    ROS_INFO("iServomotor got param: %s\n", s.c_str());
    servo_angle_min = atoi(s.c_str());
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_angle_min'\n");
  }

  ros::spin();

  return 0;
}