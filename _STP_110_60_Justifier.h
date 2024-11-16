#ifndef _STP_110_60_JUSTIFIER_H
#define _STP_110_60_JUSTIFIER_H

#include <Arduino.h>

class STP_110_60_Justifier {
public:
    // Constructor
    STP_110_60_Justifier() {
        // Initialize any members if needed
    }

    // Function that takes an array of register values and a number of registers
    double justify(int regi_case, short unsigned int* registerValues) {
      double returnVal = 0;
      //double p =0;
      switch (regi_case) {
        case 40094:{//////40094:
           double p = ((double) registerValues[0])*65536 + (double)registerValues[1];
            // Serial.print("************************************************* ");
            // Serial.println(p);
            // Serial.println("Case 1: Value is 1");
            returnVal = p;
          break;}
        case 40073:            
            returnVal = (double) registerValues[0];
          break;
        case 40074:
            returnVal = (double) registerValues[0];
          break;
        case 40075:
            returnVal = (double) registerValues[0];
          break;
        case 40077:
            returnVal = (double) registerValues[0];
          break;
        case 40078:
            returnVal = (double) registerValues[0];
          break;
        case 40079:
            returnVal = (double) registerValues[0];
          break;
        case 40080:
            returnVal = (double) registerValues[0];
          break;
        case 40081:
            returnVal = (double) registerValues[0];
          break;
        case 40082:
             returnVal = (double) registerValues[0];
          break;
        case 40084:
            returnVal = (double) registerValues[0];
          break;
        case 40086:
            returnVal = (double) registerValues[0];
          break;
        case 40088:
            returnVal = (double) registerValues[0];
          break;
        case 41312:
            returnVal = (double) registerValues[0];
          break;
        case 41323:
            returnVal = (double) registerValues[0];
          break;
        case 41324:
            returnVal = (double) registerValues[0];
          break;
        case 41325:
            returnVal = (double) registerValues[0];
          break;
        case 41343:
            returnVal = (double) registerValues[0];
          break;
        case 41344:
            returnVal = (double) registerValues[0];
          break;
        case 41345:
            returnVal = (double) registerValues[0];
          break;
        case 41363:
            returnVal = (double) registerValues[0];
          break;
        case 41364:
            returnVal = (double) registerValues[0];
          break;
        case 41365:
            returnVal = (double) registerValues[0];
          break;
        case 41383:
            returnVal = (double) registerValues[0];
          break;
        case 41384:
            returnVal = (double) registerValues[0];
          break;
        case 41385:
            returnVal = (double) registerValues[0];
          break;
        case 41403:
            returnVal = (double) registerValues[0];
          break;
        case 41404:
            returnVal = (double) registerValues[0];
          break;
        case 41405:
            returnVal = (double) registerValues[0];
          break;
        case 41423:
            returnVal = (double) registerValues[0];
          break;
        case 41424:
            returnVal = (double) registerValues[0];
          break;
        case 41425:
            returnVal = (double) registerValues[0];
          break;
        case 41443:
            returnVal = (double) registerValues[0];
          break;
        case 41444:
            returnVal = (double) registerValues[0];
          break;
        case 41445:
            returnVal = (double) registerValues[0];
          break;
        case 41463:
            returnVal = (double) registerValues[0];
          break;
        case 41464:
            returnVal = (double) registerValues[0];
          break;
        case 41465:
            returnVal = (double) registerValues[0];
          break;
        case 41483:
            returnVal = (double) registerValues[0];
          break;
        case 41484:
            returnVal = (double) registerValues[0];
          break;
        case 41485:
            returnVal = (double) registerValues[0];
          break;
        case 41501:
            returnVal = (double) registerValues[0];
          break;
        case 41502:
            returnVal = (double) registerValues[0];
          break;        
        case 41503:
            returnVal = (double) registerValues[0];
          break;
        case 41521:
            returnVal = (double) registerValues[0];
          break;
        case 41522:
            returnVal = (double) registerValues[0];
          break;
        case 41523:
            returnVal = (double) registerValues[0];
          break;
        case 41541:
            returnVal = (double) registerValues[0];
          break;
        case 41542:
            returnVal = (double) registerValues[0];
          break;
        case 41543:
            returnVal = (double) registerValues[0];
          break;
        default:
            //Serial.println("Default case: Value does not match any case");
            returnVal = (double)registerValues[0];
            break;
    }

    return returnVal;
  }
    
};

#endif
