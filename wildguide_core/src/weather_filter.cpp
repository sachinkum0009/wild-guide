#include "wildguide_core/weather_filter.hpp"

namespace wildguide_core {
WeatherPclFilter::WeatherPclFilter(int sor_mean_k, double sor_std_dev_mul_thres,
                                   double ror_radius_search,
                                   int ror_min_neighbors)
    : sor_mean_k_(sor_mean_k), sor_std_dev_mul_thres_(sor_std_dev_mul_thres),
      ror_radius_search_(ror_radius_search),
      ror_min_neighbors_(ror_min_neighbors) {

  sor_filter_ =
      std::make_unique<pcl::StatisticalOutlierRemoval<pcl::PointXYZ>>();
  sor_filter_->setMeanK(sor_mean_k_);
  sor_filter_->setStddevMulThresh(sor_std_dev_mul_thres_);

  ror_filter_ = std::make_unique<pcl::RadiusOutlierRemoval<pcl::PointXYZ>>();
  ror_filter_->setRadiusSearch(ror_radius_search_);
  ror_filter_->setMinNeighborsInRadius(ror_min_neighbors_);
}

void WeatherPclFilter::apply_filter(
    const pcl::PointCloud<pcl::PointXYZ>::Ptr &in_cloud,
    pcl::PointCloud<pcl::PointXYZ> &out_cloud) {

  if (in_cloud->empty()) {
    return;
  }

  pcl::PointCloud<pcl::PointXYZ>::Ptr intermediate_cloud(
      new pcl::PointCloud<pcl::PointXYZ>);

  sor_filter_->setInputCloud(in_cloud);
  sor_filter_->filter(*intermediate_cloud);

  if (!intermediate_cloud->empty()) {
    ror_filter_->setInputCloud(intermediate_cloud);
    ror_filter_->filter(out_cloud);
  } else {
    out_cloud.clear();
  }
}
} // namespace wildguide_core