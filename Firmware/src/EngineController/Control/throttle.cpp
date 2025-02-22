#include "throttle.h"
#include "EngineController/StateMachine/Controlled.h"

Throttle::Throttle(EngineController& Engine):
_engine(Engine),
m_setpointPcLuT({0,200,201,1200,2200,5000},{0,2,5,5,10,10}), //THROTTLE PC setpoints LUT
m_PcAngleLuT({0,2,5,10},{0,0,105,150}) //THROTTLE OX ANGLE LUT
{};

void Throttle::setup(uint64_t ControlledTime){

    m_Pc = _engine._sensorHandler.getPressure(SensorID::ChamberPt);
    m_controlledTime = ControlledTime;

}


void Throttle::update(){

    // Updating params

    updatePc();

    m_currTime = millis();
    m_dt = m_currTime - m_prevTime;

    updatePcSetpoint();
    updateFFAngle();    

    // Update next angle
    m_nextAngle = FF() + FB();

    m_prevTime = m_currTime;

}

void Throttle::updatePc()
{
    // Update chamber pressure
    m_prevPc = m_Pc;
    m_Pc = _engine._sensorHandler.getPressure(SensorID::ChamberPt);
    
}

void Throttle::updatePcSetpoint()
{
    // Update setpoint based on LUT
    m_PcSetpoint = m_setpointPcLuT.get(m_currTime-m_controlledTime);
}

void Throttle::updateFFAngle()
{
    // Update feed forward angle based on LUT
    m_FFAngle = m_PcAngleLuT.get(m_PcSetpoint);
}



float Throttle::FF()
{
    // Returns Feed forward based of LuT
    return m_FFAngle;
}   


float Throttle::FB()
{
    // Feed back control

    m_FB = m_Pid.Pid(m_Kp, m_Ki, m_Kd, m_dt, m_Pc, m_prevPc, m_PcSetpoint);
    return m_FB;
}

float Throttle::getNextAngle()
{   
    return m_nextAngle;
}       