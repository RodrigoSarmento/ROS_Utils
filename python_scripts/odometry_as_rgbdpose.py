#!/usr/bin/env python

"""
This scrip listen to a odometry topic and publish a message 
with the following format "timestamp, x y z x y z w"
import rospy

from nav_msgs.msg import Odometry
from std_msgs.msg import String

message=""

def odometryCb(msg):
	now = rospy.get_rostime()
	global message
	message = str(now.secs)+"."+str(now.nsecs)+" "+str(msg.pose.pose.position.x)+" "+str(msg.pose.pose.position.y)\
+" "+str(msg.pose.pose.position.z)+" "+str(msg.pose.pose.orientation.x)+" "+str(msg.pose.pose.orientation.y)\
+" "+str(msg.pose.pose.orientation.z)+" "+str(msg.pose.pose.orientation.w)
	print(message)

def talker():
	pub = rospy.Publisher('ground_truth',String,queue_size = 10)
	rate = rospy.Rate(10)
	while not rospy.is_shutdown():
		pub.publish(message)
		rate.sleep()
if __name__ == "__main__":
	rospy.init_node('odometry_timestamp', anonymous=True) #make node 
	rospy.Subscriber('odom',Odometry,odometryCb)
	talker()
	rospy.spin()



