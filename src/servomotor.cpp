#include "ros/ros.h"
#include "std_msgs/String.h"
#include "rc_car/defines.h"
#include "rc_car/Command.h"
#include "rc_car/RSRMsg.h"
#include "rc_car/pwm.h"

PWM pwmServomotor(PWM_SERVOMOTOR_DIR);
int servo_period_angle_max = 0;
int servo_period_angle_0 = 0;
int servo_period_angle_min = 0;
int servo_angle_max = 0;
int servo_angle_min = 0;

void refreshPWM_Servomotor(const rc_car::CommandConstPtr& cmd)
{
  float dutyPeriod = 0.0;

  ROS_INFO("iServomotor received from tCommand: %f", cmd->dir);

  // Mise à jour du temps haut (en ns) en fonction de dir
  dutyPeriod = (servo_period_angle_max - servo_period_angle_min)/(servo_angle_max - servo_angle_min)*(cmd->dir) + servo_period_angle_0;

  if(dutyPeriod>2000000) // Supérieur à 2 ms
  {
    dutyPeriod = 2000000;
    ROS_WARN("iServomotor get a duty period > 2 ms, set to 2 ms\n");
  }
  else if(dutyPeriod<1000000) // Inférieur à 1 ms
  {
    dutyPeriod = 1000000;
    ROS_WARN("iServomotor get a duty period < 1 ms, set to 1 ms\n");
  }

  if(dutyPeriod>servo_period_angle_max)
  {
    dutyPeriod = servo_period_angle_max;
    ROS_WARN("iServomotor get a duty period > servo_period_angle_max, set to servo_period_angle_max\n");
  }
  else if (dutyPeriod<servo_period_angle_min)
  {
    dutyPeriod = servo_period_angle_min;
    ROS_WARN("iServomotor get a duty period < servo_period_angle_min, set to servo_period_angle_min\n");
  }

  if(!(pwmServomotor.setDuty(round(dutyPeriod))))
  {
    ROS_ERROR("iServomotor unable to set the duty period");
  }
}

void RSR_process(const rc_car::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iServomotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    if(!(pwmServomotor.setRunningState(false)))
    {
      ROS_ERROR("iServomotor unable to disable the servomotor");
    }
  }
  else
  {
    if(!(pwmServomotor.setRunningState(true)))
    {
      ROS_ERROR("iServomotor unable to enable the servomotor");
    }
  }

  if(RSR->reset)
  {
    if(!(pwmServomotor.setDuty(0)))
    {
      ROS_ERROR("iServomotor unable to reset the duty period");
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "iServomotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_Servomotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  if (n.getParam("/servo_period_angle_max", servo_period_angle_max))
  {
    ROS_INFO("iServomotor got param /servo_period_angle_max: %d\n", servo_period_angle_max);
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_period_angle_max'\n");
  }

  if (n.getParam("/servo_period_angle_0", servo_period_angle_0))
  {
    ROS_INFO("iServomotor got param /servo_period_angle_0: %d\n", servo_period_angle_0);
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_period_angle_0'\n");
  }

  if (n.getParam("/servo_period_angle_min", servo_period_angle_min))
  {
    ROS_INFO("iServomotor got param /servo_period_angle_min: %d\n", servo_period_angle_min);
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_period_angle_min'\n");
  }

  if (n.getParam("/servo_angle_max", servo_angle_max))
  {
    ROS_INFO("iServomotor got param /servo_angle_max: %d\n", servo_angle_max);
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_angle_max'\n");
  }

  if (n.getParam("/servo_angle_min", servo_angle_min))
  {
    ROS_INFO("iServomotor got param /servo_angle_min: %d\n", servo_angle_min);
  }
  else
  {
    ROS_ERROR("Failed to get param 'servo_angle_min'\n");
  }

  ros::spin();

  return 0;
}