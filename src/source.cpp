#include <iostream>
#include <memory>
#include <chrono>
#include <sstream>
#include <string>

#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <Eigen/Core>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>

#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>

#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>

static nav_msgs::Path path;
static ros::Publisher path_pub;

void gps_callback(const geometry_msgs::PoseStamped::ConstPtr& input)
{
  // ROS_INFO("Seq: [%d]", msg->header.seq);
  // ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  // ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  // ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);

  geometry_msgs::PoseStamped pose_from_gps;

  pose_from_gps.header.stamp = ros::Time::now();

  pose_from_gps.header.frame_id = input->header.frame_id;

  pose_from_gps.pose.position.x = input->pose.position.x;
  pose_from_gps.pose.position.y = input->pose.position.y;
  pose_from_gps.pose.position.z = input->pose.position.z;

  pose_from_gps.pose.orientation.x = input->pose.orientation.x;
  pose_from_gps.pose.orientation.y = input->pose.orientation.y;
  pose_from_gps.pose.orientation.z = input->pose.orientation.z;
  pose_from_gps.pose.orientation.w = input->pose.orientation.w;

  path.header.stamp = pose_from_gps.header.stamp;
  path.header.frame_id = input->header.frame_id;
  path.poses.push_back(pose_from_gps);
//  std::cout << path.header.frame_id<<std::endl;
  path_pub.publish(path);
}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "path_follow");

  ros::NodeHandle nh;

  ros::Subscriber gps_sub = nh.subscribe("/ndt_pose",10,gps_callback);
  path_pub = nh.advertise<nav_msgs::Path>("gps_path",10);

  ros::spin();
  return (0);

}
