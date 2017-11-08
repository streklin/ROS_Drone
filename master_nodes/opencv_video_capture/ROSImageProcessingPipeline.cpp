#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<ros/ros.h>
#include<image_transport/image_transport.h>
#include<sensor_msgs/image_encodings.h>

using namespace cv;

static const std::string OPENCV_WINDOW = "Image window";

void imageProcessingPipeline(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        
    } catch(cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
     
    imshow(OPENCV_WINDOW, cv_ptr->image);
    waitKey(3);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "opencv_image_pipeline");
    ros::NodeHandle nh;
    
    // testing purposes only
    namedWindow(OPENCV_WINDOW);
    
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("pi_rover/images", 1, imageProcessingPipeline);
    
    ros::spin();
        
    return 0;
}