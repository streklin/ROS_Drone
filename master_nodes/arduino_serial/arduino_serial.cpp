#include<stdio.h>
#include<unistd.h>

class ArduinoSerialCommunications {
private:
    char* arduino_serial_port_;

public:
    ArduinoSerialCommunications(char* serial_port) {
        this->arduino_serial_port_ = serial_port;
    }
    
    void sendMessage(const char* msg) {
        FILE* pfile;
        
        pfile = fopen(this->arduino_serial_port_, "w");
        
        if (pfile == NULL) {
            throw "Error: Unable to communicate with Arduino.";
        }
        
        fprintf(pfile, msg);
        fclose(pfile);
    }
};

