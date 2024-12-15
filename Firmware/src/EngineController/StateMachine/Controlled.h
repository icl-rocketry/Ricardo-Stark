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

    uint64_t m_Controlled_duration = 5000;
    uint64_t m_Controlled_Command_time;

    std::vector<uint32_t> time_array = {0,500, 514, 528, 542, 556, 570, 584, 598, 612, 626, 640, 654, 668, 682, 696, 710, 724, 738, 752, 766, 780, 794, 808, 822, 836, 850, 864, 878, 892, 906, 920, 934, 948, 962, 976, 990, 1004, 1018, 1032, 1046, 1060, 1074, 1088, 1102, 1116, 1130, 1144, 1158, 1172, 1186, 1200, 1214, 1228, 1242, 1256, 1270, 1284, 1298, 1312, 1326, 1340, 1354, 1368, 1382, 1396, 1410, 1424, 1438, 1452, 1466, 1480};
    std::vector<float> m_OxAngle = {180};
    std::vector<float> m_FuelAngle = {110,110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180};

    uint8_t m_timeIndex = 0;

    float  _nextOxAngle;
    float  _nextFuelAngle;

    float m_OxAngleLim = 150; 
    float m_FuelAngleLim = 180;

    float m_throttleOx_min = 0; 
    float m_throttleFuel_min = 0;

    float m_Ox_FF;
    float m_Fuel_FF;

    float m_OxPercent = 0;
    float m_FuelPercent = 0;

    float m_FuelExtra = -0.45;

   
    // Throttle Params

    float m_OxThrottleRange;
    float m_FuelThrottleRange;

    void updateThrottle();
    void updateOF();

    Throttle m_throttle;
    OF m_OF;

   

};