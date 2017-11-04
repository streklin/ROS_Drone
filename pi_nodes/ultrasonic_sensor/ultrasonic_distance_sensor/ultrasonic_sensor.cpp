#include<wiringPi.h>

/*
WiringPi interface for ultrasonic sensor.
*/
class UltrasonicSensor {
    private:
        /* GPIO pin number for wiringPi. */
        int pin_number_;
        
        /* Track sensor state, do not initiate a new request while the old one is still *
         * busy */
        bool is_busy_;
        
    protected:
        /* Send a 10 microsecond pulse to the sensor to trigger a test pulse. */
        void sendTestPulse() {
            pinMode(this->pin_number_, OUTPUT);
            digitalWrite(this->pin_number_, HIGH);
            delayMicroseconds(10);
        }
        
        /* Wait for the ulrasonic sensor to provide feedback.  Does not wait for
        longer than 50 milliseconds. */
        void waitForReturn() {
            pinMode(this->pin_number_, INPUT);
            int result = digitalRead(this->pin_number_);
            
            int start_time = millis();
            
            while(result == 0) {
                result = digitalRead(this->pin_number_);
                
                int current_time = millis();
                if (current_time - start_time > 50) {
                    throw "Error: Ultrasonic sensor did not respond";
                }
            }
        }
        
        /* Measures the length of the current ultrasonic sensors response in 
         * microseconds. */
        int measureResponse() {
            
            int start_time = micros();
            while(digitalRead(this->pin_number_) == 1) {}
            int end_time = micros();
            
            return end_time - start_time;
        }
        
    public:
        UltrasonicSensor(int pin_number) {
            // setup wiring pi (just in case)
            if (wiringPiSetup() == -1) {
                throw "Error: Unable to configure wiring pi";
            }
            
            this->pin_number_ = pin_number;
            this->is_busy_ = false;
            
        }
        
        /* Sends a pulse on the ultrasonic sensor and waits for an echo back.  Returns -1.0f
         * if there is already a cycle in progress. */
        float getSensorReading() {
            // are we still doing a ping request?
            if (this->is_busy_) {
                return -1.0f;
            }
            
            sendTestPulse();
            waitForReturn();
            
            int pulseWidth = measureResponse();      
            float distance = (float)pulseWidth / 58.0f;
    
            return distance;
        }
    
    
}
