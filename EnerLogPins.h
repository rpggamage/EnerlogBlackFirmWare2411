#ifndef ENERLOGPINS_H
#define ENERLOGPINS_H

//#define LTE_RESET_PIN 21
//#define LTE_PWRKEY_PIN 37

#define MCU_STAT 1
#define SW_UP 18
#define SW_DWN 16
#define SW_SEL 7

// SIM7600 GPIO Config
#define AT_RST 21
#define AT_POWER 37  // SIM7000 PWR_KEY
#define sim_rxPin 36
#define sim_txPin 35

// RS45 Pin config
#define rs485_rxPin 4
#define rs485_txPin 5
#define rs485_enPin 6

// Define the pins for HSPI interface for SD Card
#define HSPI_MISO 38
#define HSPI_MOSI 39
#define HSPI_SCLK 40
#define HSPI_CS 41

// OLED Display config
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define RESET_P 14        // Tie the Wiz820io/W5500 reset pin to ESP32 GPIO26 pin.
#define CS_P 10

/*
 * W5500 "hardware" MAC address.
 */
uint8_t eth_MAC[] = { 0x02, 0xF0, 0x0D, 0xBE, 0xEF, 0x01 };

// Enter a MAC address and IP address for your controller below.
byte mac[] = {
    0x02, 0xF0, 0x0D, 0xBE, 0xEF, 0x01
};
//IPAddress ip(169, 254, 200, 220);     // The IP address will be dependent on your local network
IPAddress ip(169,254,12,12);  //http://169.254.12.x/    // The IP address will be dependent on your local network

/*
 * Define the static network settings for this gateway's ETHERNET connection
 * on your LAN.  These values must match YOUR SPECIFIC LAN.  The "eth_IP"
 * is the IP address for this gateway's ETHERNET port.
 */
IPAddress eth_IP(169,254,12,1);    // *** CHANGE THIS to something relevant for YOUR LAN. ***
IPAddress eth_MASK(255, 255, 255, 0);   // Subnet mask.
IPAddress eth_DNS(169,254,12,10);    // *** CHANGE THIS to match YOUR DNS server.           ***
IPAddress eth_GW(169,254,12,254);   // *** CHANGE THIS to match YOUR Gateway (router).     ***

#endif // ENERLOGPINS_H
