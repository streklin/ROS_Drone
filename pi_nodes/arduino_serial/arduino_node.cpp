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
    
    std::string arduino_com_port;
    nh.param("arduino_com_port", arduino_com_port);
    
    const char* port_name = arduino_com_port.c_str();
    ard = new ArduinoSerialCommunications(port_name);
     
    ros::Subscriber sub = nh.subscribe("/pi_rover/arduino/msg", 1000, &messageForArduino);
    ros::spin();
}

