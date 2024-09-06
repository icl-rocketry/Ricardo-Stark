#include "Controlled.h"

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include <librrc/Local/remoteactuatoradapter.h> 

#include "system.h"

Controlled::Controlled(Engine::ControlledStateInit& ControlledInitParams, Engine::ShutdownStateInit& ShutdownInitParams, EngineController& Engine):
State(EC_FLAGS::CONTROLLED,ControlledInitParams.enginestatus),
m_ShutdownInitParams(ShutdownInitParams),
_engine(Engine),
_OxMainAdapter(ControlledInitParams.OxAdapter),
_FuelMainAdapter(ControlledInitParams.FuelAdapter),
PcAngleLuT({4.2,12.0},{92.9,136.88})
{};

void Controlled::initialize()
{
    Types::EngineTypes::State_t::initialize();

    _OxMainAdapter.arm(0); 
    _FuelMainAdapter.arm(0);

    m_throttle_index = 0;
    m_Controlled_Command_time = millis();

    m_OxThrottleRange = m_OxAngleLim - m_throttleOx_min;
    m_FuelThrottleRange = m_FuelAngleLim - m_throttleFuel_min;

  
  
};

Types::EngineTypes::State_ptr_t Controlled::update()
{

    digitalWrite(PinMap::LED, HIGH);


        if (millis() - m_Controlled_Command_time > m_Controlled_duration){

        return std::make_unique<Shutdown>(m_ShutdownInitParams);

    }

    else if (m_Pc > m_maxPc){

         return std::make_unique<Shutdown>(m_ShutdownInitParams); //Kills Engine if Pc is too high

    }

    else 
    {

        if(En_Throttle == true) //Throttle control enabled
        {

            m_Ox_FF = Ox_FF(m_Pc);

            _nextOxAngle = m_Ox_FF + OxAngleFb();

            _OxMainAdapter.execute(_nextOxAngle);

        }

        if(En_OF == true) //OF control enabled
        {

        m_OxPercent = (float)(_nextOxAngle - m_throttleOx_min) / (float)(m_OxThrottleRange);

        m_Fuel_FF = Fuel_FF(_nextOxAngle);

        _nextFuelAngle = m_Fuel_FF + FuelAngleFb();

        _FuelMainAdapter.execute(_nextFuelAngle);

        }
        else //Feedforward only for simple controller
        {
            _OxMainAdapter.execute(Ox_FF(m_Pc));
            _FuelMainAdapter.execute(Fuel_FF(_nextOxAngle));

        }

        return nullptr;

    }

    

}

void Controlled::exit()
{
    Types::EngineTypes::State_t::exit();
};



float Controlled::OxAngleFb(){

    float demandPc = PcSetpoint();
    float _curr_Pc = _engine._ChamberPT.getPressure();        

    float _Pc_err = demandPc - _curr_Pc;
    float P_Angle = (float)Throttle_K_p*_Pc_err;

    float dt = (float)(esp_timer_get_time() - m_prev_int_t)/((float)1e6); //Calculate the time since the last update in s
    m_prev_int_t = esp_timer_get_time();
    m_I_err = m_I_err + _Pc_err*dt; //Increment the integral counter

    if (m_I_err > m_I_max)
    {
        m_I_err = m_I_max;
    }
    else if (m_I_err < -m_I_max)
    {
        m_I_err = -m_I_max;
    }

    if(_Pc_err * m_prev_I_err < 0){
        m_I_err = 0;
    }
    m_prev_I_err = _Pc_err;

    float I_term = Throttle_K_i*m_I_err;
    float I_angle = I_term;

    float _OxAngleFb = P_Angle + I_angle; 

    return _OxAngleFb;
};

float Controlled::PcSetpoint(){

    if (millis() - m_Controlled_Command_time > m_throttletime[m_throttle_index])
    {
        m_throttle_index++;
        m_ThrottleTime = millis();
    }

    return m_targetPc[m_throttle_index];
};


float Controlled::Ox_FF(float Pc){

    return PcAngleLuT.get(Pc);

};

float Controlled::FuelAngleFb(){

    float demand_OF_ratio = m_OFratio;
    float _curr_OF_ratio = (float)_engine._OxPT.getPressure() / (float)_engine._FuelPT.getPressure();

    float _OF_err = demand_OF_ratio - _curr_OF_ratio;

    float P_Fuel_Angle = (float)OF_K_p*_OF_err;

    float dt = (float)(esp_timer_get_time() - m_prev_int_t)/((float)1e6); //Calculate the time since the last update in s
    m_prev_int_t = esp_timer_get_time();
    m_I_err = m_I_err + _OF_err*dt; //Increment the integral counter

    if (m_I_err > m_I_max)
    {
        m_I_err = m_I_max;
    }
    else if (m_I_err < -m_I_max)
    {
        m_I_err = -m_I_max;
    }

    if(_OF_err * m_prev_I_err < 0){
        m_I_err = 0;
    }
    m_prev_I_err = _OF_err;

    float Fuel_I_term = Throttle_K_i*m_I_err;
    float Fuel_I_angle = Fuel_I_term;
   
    float _FuelAngleFb = P_Fuel_Angle + Fuel_I_angle; 

    return _FuelAngleFb;
};



float Controlled::Fuel_FF(float OxAngle){

     m_FuelPercent = m_OxPercent + m_FuelExtra;
    
    float fuelAngle = (float)(m_FuelPercent * m_FuelThrottleRange) + m_throttleFuel_min;

    if (fuelAngle < m_throttleFuel_min)
    {
        fuelAngle = m_throttleFuel_min;
    }
    
    return fuelAngle;

}


