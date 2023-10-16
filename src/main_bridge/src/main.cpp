
#include "ros/ros.h"
#include "aslan_msgs/SDControl.h"
#include "autoware_msgs/VehicleCmd.h"

#include <sstream>

aslan_msgs::SDControl sd_msg;

void vehicleCmdCallback(const autoware_msgs::VehicleCmd::ConstPtr& msg)
{
  
  sd_msg.header = msg->header;
  sd_msg.steer = msg->steer_cmd.steer;
  if(msg->brake_cmd.brake > 0){
    sd_msg.torque = -20.0*msg->brake_cmd.brake;  // range -5.0 to 5.0
  }
  else{
    sd_msg.torque = 20.0*msg->accel_cmd.accel; //range -5.0 to 5.0
  }
  

  ROS_INFO("I heard: [%d]", sd_msg.steer);
  sd_pub.publish(sd_msg);
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;
  ros::Publisher sd_pub = n.advertise<aslan_msgs::SDControl>("/sd_control", 1000);
  ros::Subscriber vehicle_cmd = n.subscribe("/vehicle_cmd", 1000, vehicleCmdCallback);

  ros::spin();

  int count = 0;
  return 0;
}

