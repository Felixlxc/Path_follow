// pose in gps in Homogenous transformation matrix;

float position_x, position_y, position_z;
position_x = Pose_in_GPS.pose.position.x;
position_y = Pose_in_GPS.pose.position.y;
position_z = pose_in_GPS.pose.position.z;

Eigen::Vector3f position(position_x, position_y, position_z);
Eigen::Quaternion q_gps;
q_gps.w() = pose_in_GPS.pose.orientation.w;
q_gps.x() = pose_in_GPS.pose.orientation.x;
q_gps.y() = pose_in_GPS.pose.orientation.y;
q_gps.z() = pose_in_GPS.pose.orientation.z;

Eigen::Matrix3f rot_gps = q_gps.normalized().toRotationMatrix();

Eigen::Matrix4f gps_pose;
gps_pose.rightCols<1>() = position;
gps_rotate.block<3,3>(0,0) = rot_gps;

float translation_x,translation_y,translation_z;
translation_x = ;
translation_y = ;
translation_z = ;
Eigen::Vector3f translation(translate_x, translate_y, translate_z );

Eigen::Quaternion q_trans;
q_gps.w() = ;
q_gps.x() = ;
q_gps.y() = ;
q_gps.z() = ;
Eigen::Matrix3f rot_trans = q_trans.normalized().toRotationMatrix();

Eigen::Matrix4f transformation;
transformation.rightCols<1>() = position;
transformation.block<3,3>(0,0) = rot_gps;

Eigen::Matrix4f pose_map;
pose_map = transformation*gps_pose;

geometry::msgs::PoseStamped pose_in_map;
pose_in_map.pose.position.x = pose_map(0,3);
pose_in_map.pose.position.y = pose_map(1,3);
pose_in_map.pose.position.z = pose_map(2,3);

Eigen::Quaternion q_map(pose_in_map.block<3,3>(0,0));
pose_in_map.pose.orientation.x = q_map.x();
pose_in_map.pose.orientation.y = q_map.y();
pose_in_map.pose.orientation.z = q_map.z();
pose_in_map.pose.orientation.w = q_map.w();