#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist 

def move():

    rospy.init_node('simulator_move',anonymous=True)

    velocity_publisher = rospy.Publisher('/twist_cmd', Twist, queue_size = 10)
    vel_msg = Twist()

    #just for test, move in x direction

    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0
    
    while not rospy.is_shutdown():
        t0 = rospy.Time.now.to_sec()
        time_period = 20.0
        current_time = t0
        while (current_time - t0 <= time_period):
            vel_msg.linear.x = 3.0
            velocity_publisher.publish(vel_msg)
        vel_msg.linear.x = -
        velocity_publisher.publish(vel_msg)

if __name__ == '__main__':
    try:
        #Testing our function
        move()
    except rospy.ROSInterruptException: pass