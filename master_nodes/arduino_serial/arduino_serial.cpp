#include<stdio.h>
#include <unistd.h>

class ArduinoSerialCommunications {
private:
    char* arduino_serial_port_;

public:
    ArduinoSerialCommunications(char* serial_port) {
        this->arduino_serial_port_ = serial_port;
    }
    
    void sendMessage(char* msg) {
        FILE* pfile;
        
        pfile = fopen(this->arduino_serial_port_, "w");
        
        if (pfile == NULL) {
            throw "Error: Unable to communicate with Arduino.";
        }
        
        fprintf(pfile, msg);
        fclose(pfile);
    }
    
    char* readMessage() {
        FILE* pfile;
        
        pfile = fopen(this->arduino_serial_port_, "r");
        
        if (pfile == NULL) {
            throw "Error: Unable to communicate with Arduino.";
        }
        
        char msg_buffer[256];
        
        fgets(msg_buffer, 256, pfile);
        fclose(pfile);
        
        return msg_buffer;
    }
};

/*int main() {
    ArduinoSerialCommunications ard = ArduinoSerialCommunications("/dev/ttyACM1");
    
    ard.sendMessage("f");'
    sleep(1);
    ard.sendMessage("l");
    sleep(1);
    ard.sendMessage("r");
    sleep(1);
    ard.sendMessage("s");
    return 0;
}*/