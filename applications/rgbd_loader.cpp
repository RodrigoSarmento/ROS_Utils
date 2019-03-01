
///ROS
#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>   
#include <image_transport/image_transport.h>

///Opencv
#include <cstdio>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#define APPROXIMATE


#ifdef EXACT
#include <message_filters/sync_policies/exact_time.h>
#endif
#ifdef APPROXIMATE
#include <message_filters/sync_policies/approximate_time.h>
#endif



using namespace std;
using namespace cv;
using namespace message_filters;


void callback(const sensor_msgs::ImageConstPtr& msg_rgb ,const sensor_msgs::ImageConstPtr& msg_depth);
void initRos(int argc, char** argv, string rgb_topic, string depth_topic);

int main(int argc, char** argv){
  string rgb_topic;
  string depth_topic;
  rgb_topic = "camera/rgb/image_raw"; 
  depth_topic = "camera/depth/image_raw";

  if(argc == 1){
    printf( "You can set the topics you want for"
      "rgb and depth. By default using camera/rgb/image_raw and camera/depth/image_raw as rgb and depth topics\n");
  }
  if(argc == 2){
    printf("rgb_topic : %s , depth_topic : camera/depth/image_raw as default \n", argv[1]);
    rgb_topic = argv[1];
  }
  if(argc == 3){
    printf("rgb_topic : %s , depth_topic : %s \n", argv[1], argv[2]);
    rgb_topic = argv[1];
    depth_topic = argv[2];
  }

  initRos(argc, argv, rgb_topic, depth_topic);

  return 0;
}

void callback(const sensor_msgs::ImageConstPtr& msg_rgb ,const sensor_msgs::ImageConstPtr& msg_depth){

  cv_bridge::CvImagePtr img_ptr_rgb;
  cv_bridge::CvImagePtr img_ptr_depth;
  try{
    img_ptr_depth = cv_bridge::toCvCopy(*msg_depth, sensor_msgs::image_encodings::TYPE_16UC1);
  }
  catch (cv_bridge::Exception& e){
    ROS_ERROR("cv_bridge exception1:  %s", e.what());
    return;
  }
  try{
    img_ptr_rgb = cv_bridge::toCvCopy(*msg_rgb, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e){
    ROS_ERROR("cv_bridge exception2:  %s", e.what());
    return;
  }

  Mat& mat_depth = img_ptr_depth->image;
  Mat& mat_rgb = img_ptr_rgb->image;

  mat_depth = mat_depth/5;

  cv::imshow("OPENCV_WINDOW_RGB", mat_rgb);
  cv::imshow("OPENCV_WINDOW_DEPTH", mat_depth);
  cv::waitKey(1);
}

void initRos(int argc, char** argv, string rgb_topic, string depth_topic){
  ros::init(argc, argv, "bag_loader");
  ros::NodeHandle nh;

  message_filters::Subscriber<sensor_msgs::Image> subscriber_depth(nh , depth_topic , 1);
  message_filters::Subscriber<sensor_msgs::Image> subscriber_rgb(nh , rgb_topic , 1);

  #ifdef EXACT
      typedef sync_policies::ExactTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;
  #endif
  #ifdef APPROXIMATE
      typedef sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;
  #endif


  // ExactTime or ApproximateTime take a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), subscriber_rgb, subscriber_depth );
  sync.registerCallback(boost::bind(&callback, _1, _2));

  ros::spin();
}
