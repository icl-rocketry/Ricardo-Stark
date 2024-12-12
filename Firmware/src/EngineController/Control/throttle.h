#pragma once

#include "EngineController/Control/PID.h"
#include "EngineController/Control/LuT.h"
#include "EngineController/Control/Linearinterp.h"
#include "EngineController/StateMachine/EngineController.h"
#include "Sensors/sensorID.h"
#include <Arduino.h>
#include <vector>

class Throttle
{

    public:

    Throttle(EngineController& Engine);

    void setup(uint64_t ControlledTime);
    void update();
    void updatePc();

    float FF();
    float FB();    

    float getNextAngle();     

    private:

    float m_Pc;
    float m_prevPc;
    float m_nextPc;

    uint64_t m_controlledTime;

    EngineController& _engine;

    //Setpoint LUT
    LuT<float,LinearInterp<float>> m_setpointPcLuT;
    float m_PcSetpoint;
    void updatePcSetpoint();

    // Feed Forward LUT
    LuT<float,LinearInterp<float>> m_PcAngleLuT;
    float m_FFAngle;
    void updateFFAngle();


    float m_nextAngle;
    float m_FF;
    float m_FB;

    // PID Gains
    float m_Kp = 0.0;
    float m_Ki = 0.0;
    float m_Kd = 0.0;

    uint64_t m_currTime;
    uint64_t m_prevTime;
    uint32_t m_dt;

    PID<float> m_Pid;

};