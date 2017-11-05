/*
Rover communicates with the RPi using the usb port.  RPi's
ROS node then reads the information, sends feedback, and forwards
any relevant data back to the ROS Master node.
 */

/*
 DFRobotShip V2 Rover
 */

int speed = 255; //maximum motor speed
int E1 = 6; //M1 Speed Control 
int E2 = 5; //M2 Speed Control 
int M1 = 8; //M1 Direction Control 
int M2 = 7; //M2 Direction Control 

void configureMotorController() {
  for(int i = 5; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void goForward() {
  analogWrite (E1,speed);
  digitalWrite(M1,LOW);
  analogWrite (E2,speed);
  digitalWrite(M2,LOW);
}

void goLeft() {
  analogWrite (E1,speed);
  digitalWrite(M1,LOW);
  analogWrite (E2,0);
  digitalWrite(M2,LOW);
}

void goRight() {
  analogWrite (E2,speed);
  digitalWrite(M2,LOW);
  analogWrite (E1,0);
  digitalWrite(M1,LOW);
}

void stopRover() {
  analogWrite (E1,0);
  digitalWrite(M1,LOW);

  analogWrite (E2,0);
  digitalWrite(M2,LOW);

}

/* read commands from the pi */

void getNextCommand() {
  int command;
  command = Serial.read();

  if (command == 'f') {
    goForward(); 
  } else if(command == 'r') {
    goRight();
  } else if(command == 'l') {
    goLeft();
  } else {
    stopRover();
  }
}

void setup() {
  configureMotorController();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    getNextCommand();
  }
  
}
