#ifndef LIDARPLOT_HPP_
#define LIDARPLOT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <opencv2/opencv.hpp>

#define RAD2DEG(x) ((x)*180./M_PI)

class LIDARPLOT : public rclcpp::Node
{
public:
  LIDARPLOT();

private:
  void scanCb(const sensor_msgs::msg::LaserScan::SharedPtr scan) const;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr lidar_info_sub;
};

#endif // LIDARPLOT_HPP_