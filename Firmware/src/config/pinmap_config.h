/*
**********************
* PINS               *
**********************
 */
#pragma once
#include <stdint.h>

// v2 Pins

namespace PinMap{

    
    // CAN
    static constexpr uint8_t RxCan = 10; 
    static constexpr uint8_t TxCan = 11; 
    
    // SD
    static constexpr uint8_t SdDet = 39; //change
    static constexpr uint8_t SdCs = 18;
    static constexpr uint8_t V_MOSI = 17;
    static constexpr uint8_t V_SCLK = 16;
    static constexpr uint8_t V_MISO = 15;

    // Servo
    static constexpr uint8_t ServoPWM1 = 14; 
    static constexpr uint8_t ServoPWM2 = 13; 
    static constexpr uint8_t ServoVLog = 8; 

    // Pyro
    static constexpr uint8_t PyroCont = 3; //NB this is on the pyro pin expander
    static constexpr uint8_t PyroNuke = 9;
    static constexpr uint8_t PyroPowerSwitch = 1; //NB this is on the pyro pin expander

    // LED
    // static constexpr uint8_t LED = 26; //chnage

    // ADS
    static constexpr uint8_t H_MISO = 33;
    static constexpr uint8_t H_SCLK = 47; 
    static constexpr uint8_t DRDY = 35; 
    static constexpr uint8_t ADS_Cs = 36; 
    static constexpr uint8_t H_MOSI = 34; 
    static constexpr uint8_t ADS_Clk =  37; 

    // GPIO Breakout
    static constexpr uint8_t GPIO1 = 1; 
    static constexpr uint8_t GPIO2 = 2; 
    static constexpr uint8_t GPIO4 = 4; 
    static constexpr uint8_t GPIO5 = 5; 

    // MISC
    static constexpr uint8_t Abort = 1;
    static constexpr uint8_t Turbine = 2;

    //I2C
    static constexpr uint8_t _SCL = 6;
    static constexpr uint8_t _SDA = 7;


   
};


// v1 Pins
// namespace PinMap{

    
//     // CAN
//     static constexpr uint8_t RxCan = 1; 
//     static constexpr uint8_t TxCan = 2; 
    
//     // SD
//     static constexpr uint8_t SdDet = 4;
//     static constexpr uint8_t SdEN = 5;
//     static constexpr uint8_t SdCs = 6;
//     static constexpr uint8_t V_MOSI = 7;
//     static constexpr uint8_t V_SCLK = 8;
//     static constexpr uint8_t V_MISO = 9;

//     // Servo
//     static constexpr uint8_t ServoPWM1 = 11; 
//     static constexpr uint8_t ServoPWM2 = 10; 
//     static constexpr uint8_t ServoVLog = 12; 

//     // Pyro
//     static constexpr uint8_t PyroIMon = 13;
//     static constexpr uint8_t PyroCont = 14;
//     static constexpr uint8_t PyroNuke = 15;
//     static constexpr uint8_t FuseCont = 16;

//     // LED
//     static constexpr uint8_t LED = 26;

//     // ADS
//     static constexpr uint8_t H_MISO = 33;
//     static constexpr uint8_t H_SCLK = 34; 
//     static constexpr uint8_t DRDY = 35; 
//     static constexpr uint8_t ADS_Cs = 36; 
//     static constexpr uint8_t H_MOSI = 47; 
//     static constexpr uint8_t ADS_Clk =  48; 

//     // GPIO Breakout
//     static constexpr uint8_t GPIO37 = 37; 
//     static constexpr uint8_t GPIO38 = 38; 
//     static constexpr uint8_t GPIO39 = 39; 
//     static constexpr uint8_t GPIO40 = 40; 
//     static constexpr uint8_t GPIO41 = 41; 
//     static constexpr uint8_t GPIO42 = 42; 

//     // MISC
//     static constexpr uint8_t Abort = 40;
//     static constexpr uint8_t Turbine = 41;


   
// };



