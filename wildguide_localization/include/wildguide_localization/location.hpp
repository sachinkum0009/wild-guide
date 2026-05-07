// Copyright 2026 Sachin Kumar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WILDGUIDE_LOCALIZATION_LOCATION_HPP
#define WILDGUIDE_LOCALIZATION_LOCATION_HPP

#include <rclcpp/rclcpp.hpp>
#include <string>
#include <wildguide_core/wildguide_core.hpp>

namespace wildguide_localization {
class Location {
 public:
  Location() = default;
  Location(const std::string& name, double latitude, double longitude);
  ~Location() = default;

 private:
  std::string name_;
  double latitude_;
  double longitude_;
};

}  // namespace wildguide_localization

#endif  // WILDGUIDE_LOCALIZATION_LOCATION_HPP