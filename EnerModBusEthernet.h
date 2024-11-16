#include <cstddef>
#ifndef ENERMODBUSETHERNET_H
#define ENERMODBUSETHERNET_H

#include <SPI.h>
#include <Ethernet.h>       // Ethernet library v2 is required
#include <ModbusEthernet.h>

class EnerModBusEthernet {
public:
    EnerModBusEthernet(byte* macAddress, IPAddress localIP, uint8_t ssPin);
    void begin();
    //bool readRegisters(uint16_t startReg, uint16_t numRegs, uint16_t* buffer);
    bool readRegisters(IPAddress remote,uint16_t startReg, uint16_t numRegs, short unsigned int* buffer);

    void task(); // Public method to handle Modbus tasks

private:
    IPAddress remote;
    byte* mac;
    IPAddress ip;
    uint8_t ssPin;
    ModbusEthernet mb;
};

EnerModBusEthernet::EnerModBusEthernet(byte* macAddress, IPAddress localIP, uint8_t ssPin)
    : mac(macAddress), ip(localIP), ssPin(ssPin) {}

void EnerModBusEthernet::begin() {
    Ethernet.init(ssPin);
    Ethernet.begin(mac, ip);
    delay(1000);           // give the Ethernet shield a second to initialize
    mb.client();           // Act as Modbus TCP client
}

//bool EnerModBusEthernet::readRegisters(uint16_t startReg, uint16_t numRegs, uint16_t* buffer) {
bool EnerModBusEthernet::readRegisters(IPAddress remote,uint16_t startReg, uint16_t numRegs, short unsigned int* buffer) {
    if (mb.isConnected(remote)) {
        
        ////startReg = startReg-15000; to simulate with numbers
        mb.readHreg(remote, startReg, buffer, numRegs,nullptr,1);
        delay(100); 
        mb.task();
        return true;
    } else {
        mb.connect(remote);  // Try to connect if not connected
        return false;
    }
}

void EnerModBusEthernet::task() {//didnt use
    mb.task();  // Handle Modbus tasks
    delay(120);       // Pulling interval
}

#endif
