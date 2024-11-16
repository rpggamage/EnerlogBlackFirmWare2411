#ifndef PLANTSETTINGS_H
#define PLANTSETTINGS_H

const String firebaseHost = "https://enerlogx-native-power-001-default-rtdb.asia-southeast1.firebasedatabase.app/";// with / u see in FB Realtime DB
const String firebaseAuth = "AIzaSyCgIJMXhD9iBdYqQ7L353voKW38KbfgvmA";

// Firebase credentials for conect from WiFI
#define FIREBASE_HOST "enerlogx-native-power-001-default-rtdb.asia-southeast1.firebasedatabase.app/"  // e.g., "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyCgIJMXhD9iBdYqQ7L353voKW38KbfgvmA"

const String DB_path = "/AppConfig/Data/Inverter-";
const String Settings_path = "/AppConfig/Data/Settings";
const String Status_path = "/AppConfig/Data/Status";

const String plantName = "Kalutara_spar_001";

IPAddress remoteIPs[] = {
  IPAddress(169,254,12,3),
  IPAddress(169,254,12,4)
  //IPAddress(169, 254, 200, 221),
  // IPAddress(169, 254, 200, 221),
  // IPAddress(192, 168, 1, 103),
  // IPAddress(192, 168, 1, 104)
  ///*************PLS NOTE Divice IP shuld test at EnerLogPins
};

const char* ssid = "XXXXXXXXX";
const char* password = "yyyyyyyyyy";

#endif // PLANTSETTINGS_H
