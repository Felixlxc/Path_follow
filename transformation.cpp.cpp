// pose in gps in Homogenous transformation matrix;

float position_x, position_y, position_z;
position_x = Pose_in_GPS.pose.position.x;
position_y = Pose_in_GPS.pose.position.y;
position_z = pose_in_GPS.pose.position.z;

Eigen::Vector3f translation(position_x, position_y, position_z);
Eigen::Quaternion q_gps;
q_gps.w() = pose_in_GPS.pose.orientation.w;
q_gps.x() = pose_in_GPS.pose.orientation.x;
q_gps.y() = pose_in_GPS.pose.orientation.y;
q_gps.z() = pose_in_GPS.pose.orientation.z;

Eigen::Matrix3f rot_gps = q_gps.normalized().toRotationMatrix();

Eigen::Matrix4f gps_pose;
gps_pose.rightCols<1>() = translation;
gps_rotate.block<3,3>(0,0) = rot_gps;


