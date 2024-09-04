/*
**********************
* PINS               *
**********************
 */
#pragma once
#include <stdint.h>

namespace PinMap{

    // CAN
    static constexpr uint8_t RxCan = 1; //1
    static constexpr uint8_t TxCan = 2; //2
    
    // SD
    static constexpr uint8_t SdDet = 4;
    static constexpr uint8_t SdEN = 5;
    static constexpr uint8_t SdCs = 6;
    static constexpr uint8_t V_MOSI = 7;
    static constexpr uint8_t V_SCLK = 8;
    static constexpr uint8_t V_MISO = 9;

    // Servo
    static constexpr uint8_t ServoPWM1 = 11; //11
    static constexpr uint8_t ServoPWM2 = 10; //10
    static constexpr uint8_t ServoVLog = 12; //12

    // Pyro
    static constexpr uint8_t PyroIMon = 13;
    static constexpr uint8_t PyroCont = 14;
    static constexpr uint8_t PyroNuke = 15;
    static constexpr uint8_t FuseCont = 16;

    // LED
    static constexpr uint8_t LED = 26;

    // ADS
    static constexpr uint8_t H_MISO = 33; //33
    static constexpr uint8_t H_SCLK = 34; //34
    static constexpr uint8_t DRDY = 35; //35
    static constexpr uint8_t ADS_Cs = 36; //36
    static constexpr uint8_t H_MOSI = 47; //47
    static constexpr uint8_t ADS_Clk =  48; //48

    // GPIO Breakout
    static constexpr uint8_t GPIO37 = 37; //37
    static constexpr uint8_t GPIO38 = 38; //38
    static constexpr uint8_t GPIO39 = 39; //39
    static constexpr uint8_t GPIO40 = 40; //40
    static constexpr uint8_t GPIO41 = 41; //41
    static constexpr uint8_t GPIO42 = 42; //42

   
};


