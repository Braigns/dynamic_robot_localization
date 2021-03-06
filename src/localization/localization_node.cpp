/**\file localization_node.cpp
 * \brief Description...
 *
 * @version 1.0
 * @author Carlos Miguel Correia da Costa
 */


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constants>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//#define ROSCONSOLE_MIN_SEVERITY ROSCONSOLE_SEVERITY_NONE
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constants>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <includes>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include <ros/ros.h>
#include <pcl/console/print.h>
#include <dynamic_robot_localization/localization/localization.h>
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </includes>  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



// ###################################################################################   <main>   ##############################################################################
int main(int argc, char** argv) {
	ros::init(argc, argv, "drl_localization_node");

	/*if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Info)) {
		ros::console::notifyLoggerLevelsChanged();
	}*/

	pcl::console::setVerbosityLevel(pcl::console::L_ERROR);

	ros::NodeHandlePtr node_handle(new ros::NodeHandle());
	ros::NodeHandlePtr private_node_handle(new ros::NodeHandle("~"));

	std::string localization_point_type;
	private_node_handle->param("localization_point_type", localization_point_type, std::string("PointXYZRGBNormal"));

	if (localization_point_type == "PointXYZRGBNormal") {
		ROS_INFO("Localization system using PointXYZRGBNormal point type");
		dynamic_robot_localization::Localization<pcl::PointXYZRGBNormal> localization;
		localization.setupConfigurationFromParameterServer(node_handle, private_node_handle);
		localization.startLocalization();
	} else if (localization_point_type == "PointXYZINormal") {
		ROS_INFO("Localization system using PointXYZINormal point type");
		dynamic_robot_localization::Localization<pcl::PointXYZINormal> localization;
		localization.setupConfigurationFromParameterServer(node_handle, private_node_handle);
		localization.startLocalization();
	} else {
		ROS_INFO("Localization system using PointNormal point type");
		dynamic_robot_localization::Localization<pcl::PointNormal> localization;
		localization.setupConfigurationFromParameterServer(node_handle, private_node_handle);
		localization.startLocalization();
	}

	return 0;
}
// ###################################################################################   </main>   #############################################################################
