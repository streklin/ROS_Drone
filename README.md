# ROS_Drone
This Repo is intended for tracking my work on modified version of the DFRobotshop V2 Rover.  While not having much practical
use, the main goal of this Rover is to allow me to consolidate the techniques I have learned from Udacity's Robotics Engineering
Nano-degree to ensure that I have fully understood the concepts before the next term begins.

1. It will be primarily done using ROS and C++.  While all this work could be done in python, for personal development reasons
I've decided to use C++ as the primary development language.  

2. It will be a distributed system.  At least three computers will be running ROS nodes for this Rover to run.
  a. A UX / master node which will be in charge of sending commands to the other sub-systems based on user input.
  b. A vision pipeline node for processing visual input.  This is being put on its own node primarily because it allows
  for use of my more powerful desktop machine for this time sensitive task.
  c. A raspberry pi running ROS which will interprit messages from the other ndoes and transform them into commands for the
  arduino rover it is attached to.

3. An FCN will be used to recognize the rover from the laptop (or other externals camera).  This will be used to located
the rover in the world so the system can send the proper commands.

4. Some kind of goal object will be choosen which the system will be required to guide the rover towards without smashing
into other objects.  I haven't decided what this should be yet, so details will need to wait.

Further details and diagrams to be added later.
