#include "lidarplot/lidarplot.hpp"

LIDARPLOT::LIDARPLOT() : Node("lidarplot_node")
{
  lidar_info_sub = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "scan", rclcpp::SensorDataQoS(), std::bind(&LIDARPLOT::scanCb, this, std::placeholders::_1));
}

void LIDARPLOT::scanCb(const sensor_msgs::msg::LaserScan::SharedPtr scan) const
{
  int count = scan->scan_time / scan->time_increment;
  cv::Mat img(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));

  for (int i = 0; i < count; i++)
  {
    float degree = scan->angle_min + scan->angle_increment * i;
    float distance = scan->ranges[i];
    if (distance >= scan->range_min && distance <= scan->range_max)
    {
      int x = 250 + distance * 50 * sin(degree);
      int y = 250 - distance * 50 * cos(degree);
      cv::circle(img, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);
    }
  }

  cv::imshow("Lidar Plot", img);
  cv::waitKey(1);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<LIDARPLOT>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}