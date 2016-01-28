#include "ros/ros.h"
#include "std_msgs/String.h"
#include "rc_car/defines.h"
#include "rc_car/Command.h"
#include "rc_car/RSRMsg.h"
#include "rc_car/pwm.h"

PWM pwmDCmotor(PWM_DC_MOTOR_DIR);
int DCmotor_period_speed_max = 0;
int DCmotor_period_speed_0 = 0;
int DCmotor_period_speed_min = 0;
int DCmotor_speed_max = 0;
int DCmotor_speed_min = 0;

void refreshPWM_DCmotor(const rc_car::CommandConstPtr& cmd)
{
  float dutyPeriod = 0.0;

  ROS_INFO("iDCmotor received from tCommand: %f", cmd->speed);

  // Mise à jour du temps haut (en ns) en fonction de speed
  dutyPeriod = (DCmotor_period_speed_max - DCmotor_period_speed_min)/(DCmotor_speed_max - DCmotor_speed_min)*(cmd->speed) + DCmotor_period_speed_0;

  if(dutyPeriod>2000000) // Supérieur à 2 ms
  {
    dutyPeriod = 2000000;
    ROS_WARN("iDCmotor get a duty period > 2 ms, set to 2 ms\n");
  }
  else if(dutyPeriod<1000000) // Inférieur à 1 ms
  {
    dutyPeriod = 1000000;
    ROS_WARN("iDCmotor get a duty period < 1 ms, set to 1 ms\n");
  }

  if(dutyPeriod>DCmotor_period_speed_max)
  {
    dutyPeriod = DCmotor_period_speed_max;
    ROS_WARN("iDCmotor get a duty period > DCmotor_period_speed_max, set to DCmotor_period_speed_max\n");
  }
  else if (dutyPeriod<DCmotor_period_speed_min)
  {
    dutyPeriod = DCmotor_period_speed_min;
    ROS_WARN("iDCmotor get a duty period < DCmotor_period_speed_min, set to DCmotor_period_speed_min\n");
  }

  if(!(pwmDCmotor.setDuty(round(dutyPeriod))))
  {
    ROS_ERROR("iDCmotor unable to set the duty period");
  }
}

void RSR_process(const rc_car::RSRMsgConstPtr& RSR)
{
  ROS_INFO("iDCmotor received from tRSR: %s %s", (RSR->run)?"run":"stop", (RSR->reset)?"reset":"no_reset");

  if(!(RSR->run))
  {
    if(!(pwmDCmotor.setRunningState(false)))
    {
      ROS_ERROR("iDCmotor unable to disable the DCmotor");
    }
  }
  else
  {
    if(!(pwmDCmotor.setRunningState(true)))
    {
      ROS_ERROR("iDCmotor unable to enable the DCmotor");
    }
  }

  if(RSR->reset)
  {
    if(!(pwmDCmotor.setDuty(0)))
    {
      ROS_ERROR("iDCmotor unable to reset the duty period");
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "iDCmotor");

  ros::NodeHandle n;

  ros::Subscriber tRSR_sub = n.subscribe("tRSR", 1000, RSR_process);
  ros::Subscriber tCommand_sub = n.subscribe("tCommand", 1000, refreshPWM_DCmotor);
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  if (n.getParam("/DCmotor_period_speed_max", DCmotor_period_speed_max))
  {
    ROS_INFO("iDCmotor got param /DCmotor_period_speed_max: %d\n", DCmotor_period_speed_max);
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_period_speed_max'\n");
  }

  if (n.getParam("/DCmotor_period_speed_0", DCmotor_period_speed_0))
  {
    ROS_INFO("iDCmotor got param /DCmotor_period_speed_0: %d\n", DCmotor_period_speed_0);
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_period_speed_0'\n");
  }

  if (n.getParam("/DCmotor_period_speed_min", DCmotor_period_speed_min))
  {
    ROS_INFO("iDCmotor got param /DCmotor_period_speed_min: %d\n", DCmotor_period_speed_min);
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_period_speed_min'\n");
  }

  if (n.getParam("/DCmotor_speed_max", DCmotor_speed_max))
  {
    ROS_INFO("iDCmotor got param /DCmotor_speed_max: %d\n", DCmotor_speed_max);
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_speed_max'\n");
  }

  if (n.getParam("/DCmotor_speed_min", DCmotor_speed_min))
  {
    ROS_INFO("iDCmotor got param /DCmotor_speed_min: %d\n", DCmotor_speed_min);
  }
  else
  {
    ROS_ERROR("Failed to get param 'DCmotor_speed_min'\n");
  }

  ros::spin();

  return 0;
}