#include "ros/ros.h"
#include "std_msgs/String.h"
#include "rc_car/defines.h"
#include "rc_car/Command.h"
#include "rc_car/RSRMsg.h"
#include "rc_car/SwitchMsg.h"
#include "rc_car/pwm.h"

PWM pwmSwitch(PWM_SWITCH_DIR);

void switch_PWM_source(const rc_car::SwitchMsgConstPtr& switchMsg, ros::Publisher* tRSR_pub)
{
  rc_car::RSRMsg msg;

  ROS_INFO("iSwitchMode received from tSwitchMode: %s", (switchMsg->modeAuto)?"auto":"manual");

  if(switchMsg->modeAuto)
  {
    if(!(pwmSwitch.setDuty(PWM_SWITCH_PERIOD_AUTO)))
    {
      ROS_ERROR("iSwitchMode unable to set the duty period");
    }
    msg.run = true;
    msg.reset = false;
    tRSR_pub->publish(msg);
  }
  else
  {
    if(!(pwmSwitch.setDuty(PWM_SWITCH_PERIOD_MAN)))
    {
      ROS_ERROR("iSwitchMode unable to set the duty period");
    }
    msg.run = false;
    msg.reset = false;
    tRSR_pub->publish(msg);
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "iSwitchMode");

  ros::NodeHandle n;

  ros::Publisher tRSR_pub = n.advertise<rc_car::RSRMsg>("tRSR", 1000);
  ros::Subscriber tSwitch_sub = n.subscribe("tSwitchMode", 1000, boost::bind(&switch_PWM_source, _1, &tRSR_pub));
  //ros::Publisher tError_pub = n.advertise<Error>("tError", 1000);

  ros::spin();

  return 0;
}