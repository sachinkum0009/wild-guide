#include "wildguide_core/weather_filter.hpp"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  wildguide_core::WeatherPclFilter weather_pcl_filter(10, 1.0, 1.0, 20);
  // weather_pcl_filter.apply_filter(const pcl::PointCloud<pcl::PointXYZ>::Ptr
  // &in_cloud, pcl::PointCloud<pcl::PointXYZ> &out_cloud);
  rclcpp::shutdown();
  return 0;
}