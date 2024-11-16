#ifndef SIM7600_H
#define SIM7600_H

#include <SoftwareSerial.h>
#include "DebugSerial.h"
#include "EnerLogPins.h"

class SIM7600 {
public:
    SIM7600(int rxPin, int txPin, long baudRate, DebugSerial &debugSerial)
        : simSerial(rxPin, txPin), baudRate(baudRate), debugSerial(debugSerial) {}

    void begin() {
              // Reinitialize SoftwareSerial at 9600 baud
        simSerial.end();
        simSerial.begin(baudRate);
        pinMode(AT_RST, OUTPUT);
        digitalWrite(AT_RST, LOW);
        pinMode(AT_POWER, OUTPUT);
        digitalWrite(AT_POWER, LOW);
        delay(100);
        digitalWrite(AT_POWER, HIGH);
        delay(2000);
        digitalWrite(AT_POWER, LOW);
        delay(5000);

        sendData("AT+CCID", 3000, DEBUG);
        sendData("AT+CREG?", 3000, DEBUG);
        sendData("AT+CGATT=1", 1000, DEBUG);
        sendData("AT+CGACT=1,1", 1000, DEBUG);
        sendData("AT+CGDCONT=1,\"IP\",\"mobitel\"", 1000, DEBUG);
    }

    String sendData(const String &command, const int timeout, boolean debug) {
        String response = "";
        debugSerial.print("Command: ");
        debugSerial.println(command);
        simSerial.println(command);

        long int time = millis();
        while ((time + timeout) > millis()) {
            while (simSerial.available()) {
                char c = simSerial.read();
                response += c;
            }
        }

        if (debug) {
            debugSerial.print("Response: ");
            debugSerial.println(response);
        }

        return response;
    }

    String getCurrentTime() {
        // Perform NTP request via SIM7600E
        sendData("AT+CNTP=\"pool.ntp.org\",22", 3000, DEBUG); // Set NTP server
        String response = sendData("AT+CNTP", 5000, DEBUG); // Request time update

        // Get current time
        if (response.indexOf("OK") != -1) {
            response = sendData("AT+CCLK?", 3000, DEBUG); // Get current time
            int startIndex = response.indexOf("\"") + 1;
            int endIndex = response.indexOf("\"", startIndex);
            String dateTime = response.substring(startIndex, endIndex);

            // Parse dateTime "yy/MM/dd,hh:mm:ss±tz" format
            String year = "20" + dateTime.substring(0, 2);
            String month = dateTime.substring(3, 5);
            String day = dateTime.substring(6, 8);
            String time = dateTime.substring(9, 17);

            // Format into "YYYY-MM-DDTHH:MM:SS"
            String formattedDateTime = year + "-" + month + "-" + day + "T" + time;

            debugSerial.print("Formatted Time: ");
            debugSerial.println(formattedDateTime);
            return formattedDateTime;
        } else {
            debugSerial.println("Failed to get current time");
            return "";
        }
    }
// void setBaudRate9600() {// before that you need to know current BR
//     String response = sendData("AT+IPR=9600", 1000, DEBUG);
//     if (response.indexOf("OK") != -1) {
//         debugSerial.println("Baud rate set to 9600 successfully.");
//         //simSerial.begin(9600); // Reinitialize SoftwareSerial at 9600 baud
//         baudRate = 9600;
//         simSerial.end();
//         simSerial.begin(baudRate);
//     } else {
//         debugSerial.println("Failed to set baud rate to 9600.");
//     }
//     sendData("AT&W", 1000, DEBUG);

// }
void setBaudRate9600() {
    // Send command to set baud rate to 9600
    String response = sendData("AT+IPR=9600", 1000, DEBUG);
    
    if (response.indexOf("OK") != -1) {
      baudRate=9600;
        debugSerial.println("Baud rate set to 9600 successfully.");
        
        // Reinitialize SoftwareSerial at 9600 baud
        simSerial.end();
        simSerial.begin(9600);
        
        // Save configuration permanently
        response = sendData("AT&W", 1000, DEBUG);
        
        if (response.indexOf("OK") != -1) {
            debugSerial.println("Baud rate setting saved permanently.");
        } else {
            debugSerial.println("Failed to save baud rate setting.");
        }
    } else {
        debugSerial.println("Failed to set baud rate to 9600.");
        baudRate=9600;
    }
}

private:
    SoftwareSerial simSerial;
    long baudRate;
    DebugSerial &debugSerial;
};

#endif // SIM7600_H
