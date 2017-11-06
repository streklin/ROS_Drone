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

int LED_PIN = 13; //default led for arduino

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

void goBackwards() {
  analogWrite (E1,speed);
  digitalWrite(M1,HIGH);

  analogWrite (E2,speed);
  digitalWrite(M2,HIGH);
  
}

void blinkLED() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
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
  } else if(command == 'b') {
    goBackwards();
  } else if(command == 's') {
    stopRover();
  } else if(command == 'g') {
    // used to let the user know that the ROS system has acheived its goal.
    stopRover();
    blinkLED();
  }
}

void setup() {
  //set led pin mode to output
  pinMode(LED_PIN, OUTPUT);
  
  configureMotorController();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    getNextCommand();
  }
  
}
