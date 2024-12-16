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

    std::vector<uint32_t> time_array = {0,1000, 1013, 1026, 1039, 1052, 1065, 1078, 1091, 1104, 1117, 1130, 1143, 1156, 1169, 1182, 1195, 1208, 1221, 1234, 1247, 1260, 1273, 1286, 1299, 1312, 1325, 1338, 1351, 1364, 1377, 1390, 1403, 1416, 1429, 1442, 1455, 1468, 1481, 1494, 1507, 1520, 1533, 1546, 1559, 1572, 1585, 1598, 1611, 1624, 1637, 1650, 1663, 1676, 1689, 1702, 1715, 1728, 1741, 1754, 1767, 1780, 1793, 1806, 1819, 1832, 1845, 1858, 1871, 1884, 1897, 1910, 1923, 1936, 1949, 1962, 1975, 1988, 2001, 2014, 2027, 2040};
    std::vector<float> m_OxAngle = {180};
    std::vector<float> m_FuelAngle = {100,100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180};

    uint8_t m_timeIndex = 0;

    float  _nextOxAngle;
    float  _nextFuelAngle;

    float m_OxAngleLim = 150; 
    float m_FuelAngleLim = 180;

    float m_throttleOx_min = 105; 
    float m_throttleFuel_min = 100;

    float m_Ox_FF;
    float m_Fuel_FF;

    float m_OxPercent = 0.0;
    float m_FuelPercent = 0.0;

    float m_FuelExtra = 0.0;

    // OX / Fuel Lead timing

    uint32_t m_OxDelay = 200;
    uint32_t m_FuelDelay = 0;

   
    // Throttle Params

    float m_OxThrottleRange;
    float m_FuelThrottleRange;

    void updateThrottle();
    void updateOF();

    Throttle m_throttle;
    OF m_OF;

   

};