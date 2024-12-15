#pragma once

#include "EngineController/Control/PID.h"
#include "EngineController/Control/LuT.h"
#include "EngineController/Control/Linearinterp.h"
#include "EngineController/StateMachine/EngineController.h"
#include <Arduino.h>
#include <vector>

class OF
{

public:

    OF(EngineController& Engine);

    void setup();
    void update();

    void setupPts();
    void updateOF();    //Iterative OF update
    float getOF();      //Returns Current OF
    float getCalcFuelFlow(); //Returns Calculated Fuel Mass Flow Rate

private:

EngineController& _engine;

// OF Calculator

LuT<float,LinearInterp<float>> m_CstarTable;

float m_startOF = 1.5;
uint8_t N = 10;
float m_comb_eff = 0.95;
float m_fuelrho = 800.0;
float m_throatD = 13.54e-3;
float m_throatA = 3.14*m_throatD*m_throatD/4;
float m_CdaFuel = 0.75*5.14e-6;

float m_mdotTotal;
float m_mdotFuel;
float m_mdotOx;
float _currPc;
float _WarmFuelInjP;

float m_currOF;
float m_loopOF;

};