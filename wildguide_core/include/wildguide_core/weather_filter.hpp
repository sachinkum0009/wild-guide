#ifndef WILDGUIDE_FILTER_HPP_
#define WILDGUIDE_FILTER_HPP_

#include <memory>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace wildguide_core {

class WeatherPclFilter {
public:
  WeatherPclFilter(int sor_mean_k, double sor_std_dev_mul_thres,
                   double ror_radius_search, int ror_min_neighbors);
  ~WeatherPclFilter() = default;

  /**
   * @brief Processes the input cloud through SOR and ROR filters.
   * @param in_cloud Pointer to the raw input point cloud.
   * @param out_cloud Reference to the filtered output point cloud.
   */
  void apply_filter(const pcl::PointCloud<pcl::PointXYZ>::Ptr &in_cloud,
                    pcl::PointCloud<pcl::PointXYZ> &out_cloud);

private:
  // Filter Objects
  std::unique_ptr<pcl::StatisticalOutlierRemoval<pcl::PointXYZ>> sor_filter_;
  std::unique_ptr<pcl::RadiusOutlierRemoval<pcl::PointXYZ>> ror_filter_;

  // SOR Parameters
  int sor_mean_k_;
  double sor_std_dev_mul_thres_;

  // ROR Parameters
  double ror_radius_search_;
  int ror_min_neighbors_;
};

} // namespace wildguide_core
#endif // WILDGUIDE_FILTER_HPP_