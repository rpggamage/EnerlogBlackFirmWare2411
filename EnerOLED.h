#ifndef ENEROLED_H
#define ENEROLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "logo.h"

// OLED Display config
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class EnerOLED {
public:
  EnerOLED();
  void initDisplay();
  void displayTextCentered(const char* text);
  void showInitialScreen();
  void showBootingScreen();
  void showRS485Initialized();
  void showSystemStarting();
  void showFunctionSelection();
  void showCurrent_task(String Tsk); 
  void debugMessage(const char* text);
  void showCurrentStatus(String arr[]);
  void displayTextFromLeft(const char* text, int16_t y);

private:
  Adafruit_SSD1306 display;
};

EnerOLED::EnerOLED() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void EnerOLED::initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.drawBitmap(0, 0, Enerlogo_bmp128x32, 128, 32, WHITE);
  display.display();
  delay(4000);
  display.clearDisplay();
}

void EnerOLED::displayTextCentered(const char* text) {
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int16_t x = (SCREEN_WIDTH - w) / 2;
  int16_t y = (SCREEN_HEIGHT - h) / 2;
  display.setCursor(x, y);
  display.print(text);
  display.display();
}
void EnerOLED::displayTextFromLeft(const char* text, int16_t y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int16_t x = 0;//(SCREEN_WIDTH - w) / 2;
  //int16_t y = (SCREEN_HEIGHT - h) / 2;
  display.setCursor(x, y);
  display.print(text);
  display.display();
}
void EnerOLED::debugMessage(const char* text) {
  display.clearDisplay();
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int16_t x = (SCREEN_WIDTH - w) / 2;
  int16_t y = (SCREEN_HEIGHT - h) / 2;
  display.setCursor(x, y);
  display.print(text);
  display.display();
}
void EnerOLED::showInitialScreen() {
  // display.clearDisplay();
  // display.setTextSize(2);
  // display.setCursor(0, 0);
  // // displayTextCentered("IOT CONTROLLER");
  // // display.setTextSize(1);
  // // display.setCursor(20, 0);
  displayTextCentered("ENER LOG POWER ON");
  delay(3000);
  //display.clearDisplay();
}






void EnerOLED::showBootingScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  displayTextCentered("Booting up...");
  display.display();
  delay(2000);
}

void EnerOLED::showRS485Initialized() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("RS485 Initialized");
  display.display();
  delay(2000);
}

void EnerOLED::showSystemStarting() {
  display.clearDisplay();
  display.setCursor(0, 0);
  displayTextCentered("System starting up...");
  display.display();
  delay(2000);
}

void EnerOLED::showFunctionSelection() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Select Function:");
  display.println("SIMCOM");
  display.println("SD");
  display.println("ETH");
  display.display();
}

// void EnerOLED::showCurrentStatus() {
//   display.clearDisplay();

//   displayTextFromLeft("INV: XX", 0);//0

//   displayTextFromLeft("/PWR: XXXXX",8);//1

//   displayTextFromLeft("TY : XXXXX",16);//2

//   displayTextFromLeft("TM : 2024-08-18T21:58:21",24);//3

// }
void EnerOLED::showCurrentStatus(String arr[]) {
  display.clearDisplay();

  String s_inv="";
  s_inv = "INV: " + arr[0];
  displayTextFromLeft(s_inv.c_str(), 0);//0
 
  String s_pwr="";
  s_pwr = "PWR: " + arr[1] + "   kW";
  displayTextFromLeft(s_pwr.c_str(),8);//1

  
  long wattValue = arr[2].toInt(); // Convert the string to an integer
  float gigawattValue = wattValue / 1000000000.0; // Convert to gigawatts
  String gigawattValueStr = String(gigawattValue, 6); // Keep 3 decimal places  
  String s_ty="";
  s_ty = "TY: " + gigawattValueStr +"  GWh";
  displayTextFromLeft(s_ty.c_str(),16);//2

  String s_time ="";
  s_time = "TM : "+ arr[3];
  displayTextFromLeft(s_time.c_str(),24);//3

}
void EnerOLED::showCurrent_task(String Tsk) {

 display.clearDisplay();
 displayTextCentered(Tsk.c_str());

}

#endif // ENEROLED_H
