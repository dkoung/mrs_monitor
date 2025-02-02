#ifndef MRS_MONITOR_FLEET_H
#define MRS_MONITOR_FLEET_H

#include <mrs_monitor/robot.h>
#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <mrs_monitor/Cancel.h>
#include <mrs_monitor/Estimate.h>
#include <mrs_monitor/Move.h>
#include <mrs_monitor/Status.h>
#include <nav_msgs/GetPlan.h>

namespace mrs_monitor
{

class Fleet
{
public:
  Fleet();

private:

  Robot* getRobot(const std::string &name);

  ros::NodeHandle nh;
  std::vector<std::unique_ptr<Robot>> fleet;
  std::map<Robot*, nav_msgs::Path> last_paths;
  tf2_ros::Buffer tf_buffer;
  tf2_ros::TransformListener tf_listener;
  ros::Publisher goals_pub;

  // advertized services and their callbacks
  ros::ServiceServer estimate_srv, move_srv, status_srv;
  bool estimateCallback(EstimateRequest &req, EstimateResponse &res);
  bool moveCallback(MoveRequest &req, MoveResponse &);
  bool statusCallback(StatusRequest &req, StatusResponse &res);  

  // cancel mission
  ros::ServiceServer cancel_srv;
  bool cancelCallback(CancelRequest &req, CancelResponse &res);

  // global planning service - used for all estimations  
  ros::ServiceClient plan_srv;
  nav_msgs::GetPlan last_plan;
};


}

#endif // MRS_MONITOR_FLEET_H
