#include<ros/ros.h>
#include<std_msgs/String.h>
#include<string.h>
#include"arduino_serial.cpp"

ArduinoSerialCommunications *ard;

void messageForArduino(const std_msgs::String &msg) {
    const char* data = msg.data.c_str();
    ard->sendMessage(data);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "arduino_serial_node");
    ros::NodeHandle nh;
    
    /* 
     * TODO: Get this setting from a parameter server.
    */
    ard = new ArduinoSerialCommunications("/dev/ttyACM1");
    \
    ros::Subscriber sub = nh.subscribe("/pi_rover/arduino/msg", 1000, &messageForArduino);
    ros::spin();
}

