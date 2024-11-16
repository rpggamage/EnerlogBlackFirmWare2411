#ifndef SPT110_REGISTERPROFILE_H
#define SPT110_REGISTERPROFILE_H

static const int _STP_110_60_PARALLEL_READ_REGS[] PROGMEM = {
  
    40094, 40073, 40074, 40075, 40077, 40078, 40079, 40080, 40081, 
    40082, 40084, 40086, 40088,40088,

    40092, 40103, 40108, 40108, 40184,40226, //test aug04
    // 40189, 40190, 40226,
    
    41312,///////////////////////////////////////21 Adresse

    41323, 41324, 41325,
    41343, 41344, 41345, 
    41363, 41364, 41365,
    41383, 41384, 41385,
    41403, 41404, 41405,
    41423, 41424, 41425,

    41443, 41444, 41445,
    41463, 41464, 41465,
    41483, 41484, 41485,
    41501, 41502, 41503,
    41521, 41522, 41523,
    41541, 41542, 41543,//////////////////////////// 3X12 =36 Adrese , Total= 21+36 = 57
    //,30039, 30459
};
String _STP_110_60_PARAMETER_NAMES[89] = {//69

"Total_yield_final",//40094
"Grid_current_phase_L01",//40073
"Grid_current_phase_L02",//40074
"Grid_current_phase_L03",//40075
"Grid_voltage_phase_L01_against_L02",//40077

"Grid_voltage_phase_L02_against_L03",//40078
"Grid_voltage_phase_L03_against_L01",//40079
"Grid_voltage_phase_L01",//40080
"Grid_voltage_phase_L02",//40081
"Grid_voltage_phase_L03",//40082

"Power",//40084                    
"Grid_frequency",//40086//#12
"Apparent_Power",//40088
"Reactive_Power",//40088
////////////////////////////////////////////////////
"EEI_displacement_power_factor","Internal_temperature","Evt1",//40092, 40103, 40108,
"Operating_status","Grid_relay_contactor","Insulation_resistance",//  40108, 40184,40226, //test aug04
/////////////////////////
"pv_Number_of_Modules",//41312 /////////////////////////////////////// 21 Para Names

"pv_DC_current_input_01",//41323
"pv_DC_voltage_input_01",//41324
"pv_DC_power_input_01",//41325

"pv_DC_current_input_02",//41343
"pv_DC_voltage_input_02",//41343
"pv_DC_power_input_02",//41343

"pv_DC_current_input_03",//41363
"pv_DC_voltage_input_03",//41363
"pv_DC_power_input_03",//41363

"pv_DC_current_input_04",//41383
"pv_DC_voltage_input_04",//41383
"pv_DC_power_input_04",//41383

"pv_DC_current_input_05",//41403
"pv_DC_voltage_input_05",//41403
"pv_DC_power_input_05",//41403

"pv_DC_current_input_06",//41423
"pv_DC_voltage_input_06",//41423
"pv_DC_power_input_06",//41423

"pv_DC_current_input_07",//41443
"pv_DC_voltage_input_07",//41443
"pv_DC_power_input_07",//41443

"pv_DC_current_input_08",//41463
"pv_DC_voltage_input_08",//41463
"pv_DC_power_input_08",//41463

"pv_DC_current_input_09",//41483
"pv_DC_voltage_input_09",//41483
"pv_DC_power_input_09",//41483

"pv_DC_current_input_10",//41501
"pv_DC_voltage_input_10",//41501
"pv_DC_power_input_10",//41501

"pv_DC_current_input_11",//41521
"pv_DC_voltage_input_11",//41521
"pv_DC_power_input_11",//41521

"pv_DC_current_input_12",// 41541
"pv_DC_voltage_input_12",// 41542
"pv_DC_power_input_12"   // 41543
//////////////////////////// 3X12 =36 Adrese , Total= 21+36 = 57

};

static const int _STP_110_60_HOW_MANY[] PROGMEM = {
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
static const double _STP_110_60_DATA_FACTORS[] PROGMEM = {

// "Total_yield_final",//40094
// "Grid_current_phase_L01",//40073
// "Grid_current_phase_L02",//40074
// "Grid_current_phase_L03",//40075
// "Grid_voltage_phase_L01_against_L02",//40077
0.10,0.10, 0.10, 0.10, 0.10, 

// "Grid_voltage_phase_L02_against_L03",//40078
// "Grid_voltage_phase_L03_against_L01",//40079
// "Grid_voltage_phase_L01",//40080
// "Grid_voltage_phase_L02",//40081
// "Grid_voltage_phase_L03",//40082
0.10, 0.10, 0.10, 0.10, 0.10,

// "Power",//40084                    
// "Grid_frequency",//40086//#12
// "Apparent_Power",//40088
// "Reactive_Power",//40088
 10.00,0.01, 10.00,10.00, //freq(12),13,14

//"EEI_displacement_power_factor","Internal_temperature","Evt1",//40092, 40103, 40108,
0.001, 0.10, 1.00,
//"Operating_status","Grid_relay_contactor","Insulation_resistance",//  40108, 40184,40226, //test aug04
1.00,1.00, 1.00,
///////////////////////////////////////////////////////////////////////////////////////////////////////

  1.00, 0.1, 0.10,//P,I,V
  1.00, 0.1, 0.10,//2 "pv_DC_current_input_01",//41323 "pv_DC_voltage_input_01",//41324 "pv_DC_power_input_01",//41325
  1.00, 0.1, 0.10,//3
  1.00, 0.1, 0.10,//4
  1.00, 0.1, 0.10,//5
  1.00, 0.1, 0.10,//6
  1.00, 0.1, 0.10,//7
  1.00, 0.1, 0.10,//8
  1.00, 0.1, 0.10,//9
  1.00, 0.1, 0.10,//10
  1.00, 0.1, 0.10,//11
  1.00, 0.1, 0.10//,//12
             // 1.00, 0.10, 0.10, 1.00////No neeed ? count pls

};

#endif // SPT110_REGISTERPROFILE_H
