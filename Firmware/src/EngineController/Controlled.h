#pragma once

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include "enginetypes.h"
#include "enginecontroller.h"

#include "LuT.h"
#include "LinearInterp.h"

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


    // Simple Engine

    uint64_t m_Controlled_duration = 15000;
    uint64_t m_Controlled_Command_time;

    std::vector<float> time_array = {0};
    std::vector<float> m_OxAngle = {170};
    std::vector<float> m_FuelAngle = {180};

    uint8_t m_timeIndex;

    float  _nextOxAngle;
    float  _nextFuelAngle;

    float m_OxAngleLim = 180; 
    float m_FuelAngleLim = 180;

    float m_throttleOx_min = 80; 
    float m_throttleFuel_min = 105;

    float Ox_FF(float Pc);
    float Fuel_FF(float OxAngle);

    float m_Ox_FF;
    float m_Fuel_FF;

    float m_OxPercent = 0;
    float m_FuelPercent = 0;

    float m_FuelExtra = -0.45;

   
    // Throttle Params

    float m_OxThrottleRange;
    float m_FuelThrottleRange;


    float OxAngleFb();
    float PcSetpoint();
   

};