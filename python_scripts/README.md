Programs explanation
------------

odometry_as_rgbdpose : This script listen to a odometry topic and publish a new message with the rgbd format.

tf_transformation_listener : This script listen to two tf and get the transformation between then as a rgbd format message.

print_cpu_memory : This script listen to all process with the name you want and print the CPU and Memory Ram usage. e.g(rtabmap) will listen to
all process that has rtabmap in the name, you must change the variable process_name.

transform_odom_to_path : This script get a odometry topic and publish as a path topic in order to be seen 
in RVIZ, if you only have odom as tf we highly recommend you to use "Hector Trajectory Server"



