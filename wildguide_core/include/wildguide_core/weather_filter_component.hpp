#ifndef WEATHER_FILTER_COMPONENT_HPP_
#define WEATHER_FILTER_COMPONENT_HPP_

#include <pcl_conversions/pcl_conversions.h>

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

#include "weather_filter.hpp"

namespace wildguide_core {

class WeatherPclFilterComponent : public rclcpp::Node {
 public:
  explicit WeatherPclFilterComponent(
      const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
  ~WeatherPclFilterComponent() = default;

 private:
  // Callbacks
  void pclCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);

  // Subscribers
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_in_;

  // Publishers
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_out_;

  // Parameters
  int sor_mean_k_;
  double sor_std_dev_mul_thres_;
  double ror_radius_search_;
  int ror_min_neighbors_;
  sensor_msgs::msg::PointCloud2 output_cloud_;

  // weather pcl filter
  std::unique_ptr<WeatherPclFilter> weather_filter_unique_ptr_;
};

}  // namespace wildguide_core

#endif  // WEATHER_FILTER_COMPONENT_HPP_
