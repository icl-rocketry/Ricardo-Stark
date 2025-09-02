#pragma once

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include "enginetypes.h"
#include "enginecontroller.h"

#include "EngineController/Control/throttle.h"
#include "EngineController/Control/OF.h"

#include "EngineController/Control/lut.h"


class Controlled: public Types::EngineTypes ::State_t
{
    public:

    Controlled(Engine::DefaultStateInit& DefaultInitParams, RnpNetworkManager& networkmanager, EngineController& Engine);

    void initialize() override;

    Types::EngineTypes::State_ptr_t update() override;

    void exit() override;


    private:

    Engine::DefaultStateInit& m_DefaultInitParams;
    RnpNetworkManager& _networkmanager;
    EngineController& _engine;

    Types::LocalServoAdapter_t& _OxMainAdapter;
    Types::LocalServoAdapter_t& _FuelMainAdapter;

   
    // Sensor params
    float m_Pc;
    static constexpr uint16_t m_maxPc = 25;

    float m_POx; //Ox injector pressure
    float m_PF; //Fuel injector pressure


////////////////////////////

    // Simple Engine

        uint64_t m_Controlled_duration = 60000; //Duration of the controlled burn (ms)
        uint64_t m_Controlled_Command_time;

        std::vector<float> time_array = {0,100,static_cast<float>(m_Controlled_duration)}; //Float type to be compatible with LuT and Interp template
        std::vector<float> m_OxAngle = {0,95,95};
        std::vector<float> m_FuelAngle = {0,100,100};

    // OX / Fuel Lead timing

        float m_OxDelay = 0; //Ox Valve opening delay (ms)
        float m_FuelDelay = 0; //Fuel Valve opening delay (ms)

    // Valve Limits in the Controlled state

    //Max
    float m_OxAngleLim = 90; 
    float m_FuelAngleLim = 90;

    //Min
    float m_throttleOx_min = 35; 
    float m_throttleFuel_min = 35;


////////////////////////////

    uint8_t m_timeIndex = 0;

    LuT<float,LinearInterp<float>> m_OxAngleLuT;
    LuT<float,LinearInterp<float>> m_FuelAngleLuT;

    float  _nextOxAngle;
    float  _nextFuelAngle;

    float m_Ox_FF;
    float m_Fuel_FF;

    float m_OxPercent = 0.0;
    float m_FuelPercent = 0.0;

    float m_FuelExtra = 0.0;


    // Throttle Params

    float m_OxThrottleRange;
    float m_FuelThrottleRange;

    void updateThrottle();
    void updateOF();

    Throttle m_throttle;
    OF m_OF;

   

};