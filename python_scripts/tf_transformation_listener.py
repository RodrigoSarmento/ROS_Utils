#!/usr/bin/env python  
import roslib
import rospy
import tf
import geometry_msgs.msg

if __name__ == '__main__':
    rospy.init_node('tf_listener')

    listener = tf.TransformListener()

    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            now = rospy.get_rostime()
            (trans,rot) = listener.lookupTransform('/map', '/base_link', rospy.Time(0))
            print(str(now.secs)+"."+str(now.nsecs)+" "+str(trans[0])+" "+str(trans[1])\
        +" "+str(trans[2])+" "+str(rot[0])+" "+str(rot[1])\
        +" "+str(rot[2])+" "+str(rot[3]))
        except  Exception as error:
            print(error)
            
            continue

        rate.sleep()
    rospy.spin()
