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

    Controlled(Engine::DefaultStateInit& DefaultInitParams, EngineController& Engine);

    void initialize() override;

    Types::EngineTypes::State_ptr_t update() override;

    void exit() override;


    private:

    Engine::DefaultStateInit& m_DefaultInitParams;
    EngineController& _engine;

    Types::LocalServoAdapter_t& _OxMainAdapter;
    Types::LocalServoAdapter_t& _FuelMainAdapter;

   
    // Sensor params
    float m_Pc;
    static constexpr uint16_t m_maxPc = 25;

    float m_POx; //Ox injector pressure
    float m_PF; //Fuel injector pressure

    float updatePc();


    // Simple Engine

    uint16_t m_SimpleOxAngle = 150;
    uint64_t m_Controlled_duration = 15000;
    uint64_t m_Controlled_Command_time;

    float  _nextOxAngle;
    float  _nextFuelAngle;

    float m_OxAngleLim = 175; //CHANGE THESE
    float m_FuelAngleLim = 150;

    float m_throttleOx_min = 100; //CHANGE THESE
    float m_throttleFuel_min = 90;

    float Ox_FF(float Pc);
    float Fuel_FF(float OxAngle);

    float m_Ox_FF;
    float m_Fuel_FF;

    float m_OxPercent = 0;
    float m_FuelPercent = 0;

    float m_FuelExtra = -0.45;

   
    // Throttle Params
    static constexpr bool En_Throttle = true;
    uint64_t m_ThrottleTime;

    float m_OxThrottleRange;
    float m_FuelThrottleRange;

    LuT<float,LinearInterp<float>> PcAngleLuT;

   
    std::vector<float> m_targetPc = {20,15};
    std::vector<uint32_t> m_throttletime = {0,1500};

    uint8_t m_throttle_index;
    static constexpr float Throttle_K_p = 6.0;
    static constexpr float Throttle_K_i = 6.0;

    float m_prev_I_err = 0;


    uint64_t m_prev_int_t = 0;
    uint16_t m_I_err;
    float m_I_max = 5; 

    float OxAngleFb();
    float PcSetpoint();


    // OF Ratio Params
    static constexpr bool En_OF = false;
    static constexpr float m_OFratio = 2.5;

    static constexpr float OF_K_p = 6.0;
    static constexpr float OF_K_i = 6.0;

    // float FuelAngleFb();


   

};