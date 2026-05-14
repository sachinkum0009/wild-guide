#include "wildguide_core/weather_filter_component.hpp"

#include <rclcpp/node_impl.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace wildguide_core {

WeatherPclFilterComponent::WeatherPclFilterComponent(
    const rclcpp::NodeOptions& options)
    : Node("weather_pcl_filter_component", options) {
  // Declare and get parameters
  this->declare_parameter<int>("sor_mean_k", 1);
  this->declare_parameter<double>("sor_std_dev_mul_thres", 1.0);
  this->declare_parameter<double>("ror_radius_search", 1.0);
  this->declare_parameter<int>("ror_min_neighbors", 1);

  this->get_parameter("sor_mean_k", sor_mean_k_);
  this->get_parameter("sor_std_dev_mul_thres", sor_std_dev_mul_thres_);
  this->get_parameter("ror_radius_search", ror_radius_search_);
  this->get_parameter("ror_min_neighbors", ror_min_neighbors_);

  RCLCPP_INFO(this->get_logger(), "Weather PCL Filter started with");
  RCLCPP_INFO(this->get_logger(),
              "SOR Mean K: %d, SOR std dev mul thres: %.2f, ROR radius search: "
              "%.2f, ROR min neighbors: %d",
              sor_mean_k_, sor_std_dev_mul_thres_, ror_radius_search_,
              ror_min_neighbors_);
  weather_filter_unique_ptr_ = std::make_unique<WeatherPclFilter>(
      sor_mean_k_, sor_std_dev_mul_thres_, ror_radius_search_,
      ror_min_neighbors_);

  pointcloud_in_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "cloud_in", rclcpp::QoS(10),
      std::bind(&WeatherPclFilterComponent::pclCallback, this,
                std::placeholders::_1));
  pointcloud_out_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
      "cloud_out", rclcpp::QoS(10));
}

void WeatherPclFilterComponent::pclCallback(
    const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_input_cloud(
      new pcl::PointCloud<pcl::PointXYZ>());
  pcl::fromROSMsg(*msg, *pcl_input_cloud);
  pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_output_cloud_ =
      pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
  weather_filter_unique_ptr_->apply_filter(pcl_input_cloud, *pcl_output_cloud_);
  pcl::toROSMsg(*pcl_output_cloud_, output_cloud_);

  pointcloud_out_->publish(output_cloud_);
}
}  // namespace wildguide_core

RCLCPP_COMPONENTS_REGISTER_NODE(wildguide_core::WeatherPclFilterComponent)
