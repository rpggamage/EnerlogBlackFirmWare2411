#define DEBUG true // Define DEBUG before including SIM7600.h

#include <Arduino.h>
#include "PlantSettings.h"
#include "EnerLogPins.h"
#include "DebugSerial.h"
#include "SIM7600.h"
#include "FirebaseClient.h"
#include "EnerOLED.h"
//#include "EnerModBusWiFi.h"
//#include "EnerModBusRS485.h"
//#include "publicDebug.h"
#include "_STP_110_60_Justifier.h"

#include "EnerModBusEthernet.h"
#include "SPT110_RegisterProfile.h"

String DispalyParameter[4];
// const uint16_t START_REG = 16;         // Starting Modbus Hreg Offset
// const uint16_t NUM_REGS = 10;          // Number of registers to read
STP_110_60_Justifier justifier;
uint16_t start_reg = 16;         // Starting Modbus Hreg Offset
uint16_t num_reg = 10;          // Number of registers to read
bool readStatusOK = false;

//IPAddress remote(169, 254, 200, 221);// Address of Modbus Slave device
//IPAddress remote(169,254,12,3); //http://169.254.12.3/ // Address of Modbus Slave device

const int32_t showDelay = 5000;        // Show result every n'th millisecond
EnerOLED oled;

EnerModBusEthernet modbusReaderEthernet(mac, ip, 10); // SS pin

uint32_t showLast = 0;
//uint16_t registerValues[num_reg] = {0};

// Calculate the number of elements in the array
int numElements = sizeof(_STP_110_60_PARALLEL_READ_REGS) / sizeof(_STP_110_60_PARALLEL_READ_REGS[0]);
int numofInveters = sizeof(remoteIPs) / sizeof(remoteIPs[0]);

DebugSerial debugSerial;
//SIM7600 sim7600(36, 35, 9600, debugSerial); // RX, TX for SoftwareSerial
SIM7600 sim7600(36, 35, 115200, debugSerial); // RX, TX for SoftwareSerial


FirebaseClient firebaseClient(sim7600, firebaseHost, firebaseAuth, debugSerial);

String thePath = plantName + DB_path;
String theSettingPath = plantName + Settings_path;
String theStatusPath = plantName + Status_path;

void setup() {
    Serial.begin(9600);                // Open serial communications and wait for port to open
    #if defined(AVR_LEONARDO)
    while (!Serial) {}                   // wait for serial port to connect. Needed for Leonardo only
    #endif
    sim7600.begin();
    modbusReaderEthernet.begin();
    // Initialize the OLED display
    oled.initDisplay();
    // Show initial screen
    oled.showInitialScreen();    
    sim7600.setBaudRate9600();// NEED INITIALY// and set at SIM7600 sim7600(36, 35, 9600, debugSerial); // RX, TX for SoftwareSerial
    oled.showCurrent_task("ENER LOG POWER ON");
    sim7600.begin();
   
}
 
void loop() {

for (int numInv = 0; numInv < numofInveters; numInv++) {/// go for all inveters 1,2,3
  double registerValuesRed[numElements] = {0};  
  
  for (int i = 0; i < numElements; i++) {
      start_reg = _STP_110_60_PARALLEL_READ_REGS[i]; // Address of the single register to read//12 will give u power
      num_reg = _STP_110_60_HOW_MANY[i];

      short unsigned int registerValues[num_reg] = {0};  
      //uint16_t registerValues[num_reg] = {0}; 
      if (modbusReaderEthernet.readRegisters(remoteIPs[numInv],start_reg, num_reg, registerValues)) {
        oled.showCurrent_task("ETH MODBUS READ");
        readStatusOK = true;
        double justVal = justifier.justify(start_reg, registerValues); //FACTOR THINGS ALSO GOOD FOR HERE
            registerValuesRed[i] = Doubleroundoff(justVal* _STP_110_60_DATA_FACTORS[i],4);
            String valueStr = String(registerValuesRed[i]);
            //oled.debugMessage(valueStr.c_str());
        // Serial.println("----------------////-----------Multiple Set END----------------------------------------------");
        for (int j = 0; j < num_reg; j++) {/// if you read one FORLOOP runs once ,2 twice ...etc
            Serial.print("Register ");
            Serial.print(start_reg + j);
            Serial.print(": ");
            Serial.println(registerValues[j]);
            Serial.print("Justified value is ");
            Serial.println(registerValuesRed[i]);
        
        }
      } else {
          Serial.println("Failed to read registers");
          readStatusOK = false;
          oled.showCurrent_task("ETH MODBUS FAIL");
      }
  
   }
   Serial.println("-------------------------------------------------------------------------");     
//////////////////////////////////////////////////////////////////////////////////////////////
if(readStatusOK){

  String jsonString = "{";

        String currentTime = sim7600.getCurrentTime(); // Get the current time
        String Data_Reading_Error = "Inverter id  match ok";
        String Model_Name = "ST_110_60";
        String Address_inverter_device_id = "Adress-ID-"+String(numInv+1);

        jsonString += "\"data_read_time\":\"" + currentTime + "\","; // Add the time field to JSON
        jsonString += "\"Data_Reading_Error\":\"" + Data_Reading_Error + "\","; 
        jsonString += "\"Model_Name\":\"" + Model_Name + "\","; 
        jsonString += "\"Address_inverter_device-id\":\"" + Address_inverter_device_id + "\","; 

        for (size_t i = 0; i < numElements; i++) {
            jsonString += "\"" + _STP_110_60_PARAMETER_NAMES[i] + "\":\"" + String(registerValuesRed[i]) + "\"";
            
            if (i < numElements - 1) {
                jsonString += ",";
            }
        }
        jsonString += "}";

  ///////////////////////////////////////////////////////////////////////////////////////////////
    String finalPath=thePath+String(numInv+1);
    firebaseClient.sendDataToFirebase(finalPath, jsonString);//555555555555555555555
    ///////////////////////////////////////////////To firebase////////////////////////////////
    ////////////////////////////////////////////////////////////////DISPALY PARA///////////////
    //////This can be done from a loop can use in debug mode to show all paras
    DispalyParameter[0]= String(numInv+1);//time
    DispalyParameter[1]= String(registerValuesRed[10]) ;//time
    DispalyParameter[2]= String(registerValuesRed[0]) ;//time
    DispalyParameter[3]= currentTime;//time
    oled.showCurrentStatus(DispalyParameter);
    ////////////////////////////////////////////////////////////////DISPALY PARA///////////////
    
}
  delay(10000);
}

  firebaseClient.sendDataToFirebase(theSettingPath, createSettingsJson());
  delay(10000);
if(readStatusOK){
  if(firebaseClient.sendDataToFirebase(theStatusPath, createStatusJson("true"))){

  }else{
    sim7600.begin();
  }
  delay(300000);
}else{
  firebaseClient.sendDataToFirebase(theStatusPath, createStatusJson("false"));
  delay(300000);
}
}
//! modbus data handling fo SMA STP 110_60
double Doubleroundoff(double value, unsigned char prec)
{
    double pow_10 = pow(10.0f, (double)prec);
    return round(value * pow_10) / pow_10;
}
String createStatusJson( String dread) {
    // Create JSON string
    String jsonString = "{";

    // Adding the time_last_update field
    String currentTime = sim7600.getCurrentTime(); // Call the method to get the current time
    jsonString += "\"time_last_update\":\"" + currentTime + "\",";

    // Adding other fields
    jsonString += "\"connection_state\":\"BOTH_ON\",";
    jsonString += "\"data_read_status\":"+dread+",";
    jsonString += "\"restart_count\":" + String(13538) + ",";
    jsonString += "\"system_internet\":\"SIM7600E_MODEM\",";
    jsonString += "\"system_modbus\":\"TCP_MODBUS\",";
    jsonString += "\"system_port\":\"LOCAL_PLACE_READ\",";
    jsonString += "\"system_version\":\"CHT24.08\"";

    jsonString += "}";

    return jsonString; // Return the JSON string
}
String createSettingsJson() {
    // Create JSON string
    String jsonString = "{";

    // Adding fields with user status
    jsonString += "\"user_internet\":" + String(0) + ",";
    jsonString += "\"user_modbus\":" + String(0) + ",";
    jsonString += "\"user_port\":" + String(0);

    jsonString += "}";

    return jsonString; // Return the JSON string
}
String createReadDataJson() {   
// sent this code to main loop due to problem
//   return jsonString; // Return the JSON string
}
