#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<ros/ros.h>
#include<image_transport/image_transport.h>
#include<sensor_msgs/image_encodings.h>

using namespace cv;

/* Transform the Matrix provided by openCV into the ROS Image message format. */
sensor_msgs::Image convertToROSImage(Mat img) {
    cv_bridge::CvImage img_bridge;
    sensor_msgs::Image img_msg;
    
    std_msgs::Header header; 
    header.seq = 0; 
    header.stamp = ros::Time::now(); 
    
    img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::RGB8, img);
    img_bridge.toImageMsg(img_msg); 
    
    return img_msg;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "opencv_video_capture");    
    ros::NodeHandle nh;
    
    image_transport::ImageTransport it(nh);
    image_transport::Publisher publisher = it.advertise("/pi_rover/images", 1); 
    
    ros::Rate loop_rate(10);
    
    VideoCapture cap;
    
    if (!cap.open(0)) {
        ROS_ERROR("Error: Unable to communicate with Web Cam.");
    }
    
    while(ros::ok()) {
        
        Mat frame;
        cap >> frame;
        
        if( frame.empty() ) {
            ROS_ERROR("Error: Video feed disconnected.");
        }

        sensor_msgs::Image ros_img = convertToROSImage(frame);
        
        publisher.publish(ros_img);
   
        ros::spinOnce();
        loop_rate.sleep();
    }
}