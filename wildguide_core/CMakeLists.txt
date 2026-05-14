cmake_minimum_required(VERSION 3.20)
project(wildguide_core)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(PCL REQUIRED COMPONENTS common filters)
find_package(OpenMP REQUIRED)

include_directories(include ${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_library(wildguide_core src/wildguide_core.cpp)
add_library(wildguide_core::wildguide_core ALIAS wildguide_core)
target_compile_features(wildguide_core PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_include_directories(wildguide_core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(wildguide_core PRIVATE "WILDGUIDE_CORE_BUILDING_LIBRARY")

add_executable(weather_filter_node src/weather_filter.cpp src/weather_filter_node.cpp)
target_include_directories(weather_filter_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_link_libraries(weather_filter_node 
  PUBLIC 
  rclcpp::rclcpp
  ${std_msgs_TARGETS} 
  ${sensor_msgs_TARGETS}
  ${PCL_LIBRARIES} 
  OpenMP::OpenMP_CXX
  )

install(TARGETS
  weather_filter_node
  DESTINATION lib/${PROJECT_NAME})

add_library(weather_filter_component SHARED src/weather_filter_component.cpp src/weather_filter.cpp)
target_compile_options(weather_filter_component PRIVATE ${OpenMP_CXX_FLAGS})
target_include_directories(weather_filter_component  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_link_libraries(weather_filter_component
  PUBLIC 
  rclcpp::rclcpp
  rclcpp_components::component
  rclcpp_components::component_manager
  pcl_conversions::pcl_conversions
  ${std_msgs_TARGETS} 
  ${sensor_msgs_TARGETS}
  ${PCL_LIBRARIES} 
  OpenMP::OpenMP_CXX
  )

rclcpp_components_register_node(
    weather_filter_component
    PLUGIN "wildguide_core::WeatherPclFilterComponent"
    EXECUTABLE weather_filter_component_exe
)


ament_export_targets(export_weather_filter_component)
install(TARGETS weather_filter_component
        EXPORT export_weather_filter_component
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)
install(
  TARGETS wildguide_core
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(
  "include/${PROJECT_NAME}"
)
ament_export_libraries(
  wildguide_core
)
ament_export_targets(
  export_${PROJECT_NAME}
)

ament_package()
