// #ifndef FIREBASECLIENT_H
// #define FIREBASECLIENT_H

// #include "SIM7600.h"
// #include "DebugSerial.h"

// class FirebaseClient {
// public:
//   FirebaseClient(SIM7600 &sim7600, const String &host, const String &auth, DebugSerial &debugSerial)
//       : sim7600(sim7600), host(host), auth(auth), debugSerial(debugSerial) {}

//   void sendDataToFirebase(const String &path, const String &jsonData) {
//     String url = host + path + ".json?auth=" + auth;
//     String http_str = "AT+HTTPPARA=\"URL\",\"" + url + "\"\r\n";
//     sim7600.sendData("AT+HTTPINIT\r\n", 2000, DEBUG);
//     sim7600.sendData(http_str, 5000, DEBUG);

//     String httpDataCmd = "AT+HTTPDATA=" + String(jsonData.length()) + ",10000\r\n";
//     sim7600.sendData(httpDataCmd, 2000, DEBUG);
//     delay(100); // Give the module some time to process the command
//     sim7600.sendData(jsonData + "\r\n", 2000, DEBUG);

//     String response = sim7600.sendData("AT+HTTPACTION=1\r\n", 3000, DEBUG); // 1 for POST method
//     if (response.indexOf("OK") != -1) {
//       debugSerial.println("HTTPACTION command executed successfully");
//     } else {
//       debugSerial.println("HTTPACTION command failed");
//     }

//     response = sim7600.sendData("AT+HTTPTERM\r\n", 3000, DEBUG);
//     if (response.indexOf("OK") != -1) {
//       debugSerial.println("HTTPTERM command executed successfully");
//     } else {
//       debugSerial.println("HTTPTERM command failed");
//     }
//   }

// private:
//   SIM7600 &sim7600;
//   String host;
//   String auth;
//   DebugSerial &debugSerial;
// };

// #endif // FIREBASECLIENT_H
////////////////////////////////////////////////////////////////////////
#ifndef FIREBASECLIENT_H
#define FIREBASECLIENT_H

#include "SIM7600.h"
#include "DebugSerial.h"

class FirebaseClient {
public:
  FirebaseClient(SIM7600 &sim7600, const String &host, const String &auth, DebugSerial &debugSerial)
      : sim7600(sim7600), host(host), auth(auth), debugSerial(debugSerial) {}

  bool sendDataToFirebase(const String &path, const String &jsonData) {
    String url = host + path + ".json?auth=" + auth;
    String http_str = "AT+HTTPPARA=\"URL\",\"" + url + "\"\r\n";
    sim7600.sendData("AT+HTTPINIT\r\n", 2000, DEBUG);
    sim7600.sendData(http_str, 5000, DEBUG);

    String contentType = "AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n";
    sim7600.sendData(contentType, 2000, DEBUG);

    // Set the X-HTTP-Method-Override header to use PUT with a POST request
    String headerCmd = "AT+HTTPPARA=\"USERDATA\",\"X-HTTP-Method-Override: PUT\"\r\n";
    sim7600.sendData(headerCmd, 2000, DEBUG);

    String httpDataCmd = "AT+HTTPDATA=" + String(jsonData.length()) + ",10000\r\n";
    sim7600.sendData(httpDataCmd, 2000, DEBUG);
    delay(100); // Give the module some time to process the command
    sim7600.sendData(jsonData + "\r\n", 2000, DEBUG);

    String response = sim7600.sendData("AT+HTTPACTION=1\r\n", 3000, DEBUG); // 1 for POST method
    if (response.indexOf("OK") != -1) {
      debugSerial.println("HTTPACTION command executed successfully");
      return true;
    } else {
      debugSerial.println("HTTPACTION command failed");
      return false;
    }

    response = sim7600.sendData("AT+HTTPTERM\r\n", 3000, DEBUG);
    if (response.indexOf("OK") != -1) {
      debugSerial.println("HTTPTERM command executed successfully");
       return true;
    } else {
      debugSerial.println("HTTPTERM command failed");
       return false;
    }
  }

private:
  SIM7600 &sim7600;
  String host;
  String auth;
  DebugSerial &debugSerial;
};

#endif // FIREBASECLIENT_H