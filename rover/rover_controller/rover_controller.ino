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
int ULTRASONIC_PIN = 12; //ultrasonic distance sensor

int DANGER_FLAG = 0; //set to 1 if danger of falling off the table.

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

/* 
 *  Stop the rover and signal the LED to let everyone know that a goal  
 *  has been reached.
*/
void signalGoal() {
  stopRover();
  blinkLED();  
}

/* Execute any command we like, cause we are safe. */
void safeCommands(int command) {

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
    signalGoal();
  }  
}

/* We are near an edge, execute low risk commands */
void riskCommands(int command) {
  if (command == 's') {
    stopRover();
  } else if (command == 'b') {
    goBackwards();
  } else if (command == 'g') {
    signalGoal();
  }
  
}

/* read commands from the pi */
void getNextCommand() {
  int command;
  command = Serial.read();

  if (DANGER_FLAG == 0) {
    safeCommands(command);
  } else {
    riskCommands(command);
  }

}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

long ping() {
   long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(ULTRASONIC_PIN, OUTPUT);
  digitalWrite(ULTRASONIC_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_PIN, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(ULTRASONIC_PIN, INPUT);
  duration = pulseIn(ULTRASONIC_PIN, HIGH);

  cm = microsecondsToCentimeters(duration);
  return cm;
}

/* Sets the danger flag and stops the rover if we might fall off the table. */
void setDangerFlag() {
  int cm = ping();

  Serial.print(cm);
  Serial.println();

  if (cm > 5) {
    Serial.print("E");
    Serial.println();
    stopRover();
    DANGER_FLAG = 1;
  } else {
    DANGER_FLAG = 0;
  }
}

void setup() {
  //set led pin mode to output
  pinMode(LED_PIN, OUTPUT);
  
  configureMotorController();
  Serial.begin(9600);
}

void loop() {
  setDangerFlag();

  if (Serial.available() > 0) {
    getNextCommand();
  }
  
}
