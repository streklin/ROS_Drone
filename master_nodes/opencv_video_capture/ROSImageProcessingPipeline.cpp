#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<ros/ros.h>
#include<image_transport/image_transport.h>
#include<sensor_msgs/image_encodings.h>
#include"ROSOpenCVUtilities.cpp"

using namespace cv;

static const std::string OPENCV_WINDOW = "Image window";
image_transport::Publisher publisher;

void imageProcessingPipeline(const sensor_msgs::ImageConstPtr& msg) {
    Mat image = convertROSToOpenCv(msg);
    
    // pattern match for the rover
    // just draw some green circles until tensorflow is setup 
    cv::circle(image, Point(50, 50), 10, CV_RGB(0,255,0));
   
    // pespective transform
    
    
    imshow(OPENCV_WINDOW, image);
    waitKey(1);
    
    // convert back to ROS
    sensor_msgs::Image ros_image = convertToROSImage(image);
    
    // publish the image
    publisher.publish(ros_image);
    
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "opencv_image_pipeline");
    ros::NodeHandle nh;
    
    namedWindow(OPENCV_WINDOW);
    
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("pi_rover/images", 1, imageProcessingPipeline);
    
    publisher = it.advertise("pi_rover/processed_images", 1);
    
    ros::spin();
        
    return 0;
}