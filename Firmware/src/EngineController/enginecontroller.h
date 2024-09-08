#pragma once

#include <libriccore/fsm/statemachine.h>
#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <librrc/Remote/nrcremoteactuatorbase.h>
#include <librrc/Local/remoteactuatoradapter.h>
#include <librrc/Local/remotesensoradapter.h>

#include <librrc/HAL/localpwm.h>

#include <librnp/rnp_networkmanager.h>
#include <librnp/rnp_packet.h>

#include "config/types.h"
#include "config/pinmap_config.h"
#include "config/services_config.h"
#include "Sensors/ADS131M06.h"

#include <librrc/Remote/nrcremoteservo.h>
#include <librrc/Remote/nrcremoteptap.h>
#include <librrc/Remote/nrcremotepyro.h>

#include "EngineTypes.h"



// enum class EC_FLAGS:uint8_t{

//     State_Default =(1<<0),
//     IGNITION = (3 << 0),
//     CONTROLLED = (4 <<0),
//     SHUTDOWN = (5 << 0),
//     DEBUG = (6 << 0)
// };

// using EC_State_T = State<EC_FLAGS>;
// using EC_StateMachine_T = StateMachine<EC_FLAGS>;


class EngineController: public NRCRemoteActuatorBase<EngineController>
{   
    
    public:

    EngineController(RnpNetworkManager& networkmanager, NRCRemotePTap& ChamberPT, NRCRemotePTap& OxPT, NRCRemotePTap& OxInjPT);

    void setup();
    void update();

    void arm_base(int32_t arg);
    void disarm_base();
    void execute_base(int32_t arg);

    void serviceSetup();

    void ignition(packetptr_t packetptr);
    void shutdown(packetptr_t packetptr);

    void logReadings();

    uint32_t telemetry_log_delta = 5000;
    uint32_t prev_telemetry_log_time;
    uint32_t prevtime;

    RnpNetworkManager& _networkmanager;
    
    // Local Sensors
    NRCRemotePTap& _ChamberPT;
    NRCRemotePTap& _OxPT;
    NRCRemotePTap& _OxInjPT;

    // Local Actuators

    Types::LocalServo_t OxMain;
    Types::LocalServoAdapter_t OxMainAdapter;

    Types::LocalServo_t FuelMain;
    Types::LocalServoAdapter_t FuelMainAdapter;

    Types::LocalPyro_t Pyro;
    Types::LocalPyroAdapter_t PyroAdapter;

    // const Types::LocalServoMap_t localServoMap = {&OxMain,&FuelMain};

    // Types::LocalPyro_t Pyro;
    // RemoteActuatorAdapter<ArduinoGpio> PyroAdapter;


    uint8_t OxMainservice = (uint8_t) Services::ID::Servo1;
    uint8_t FuelMainservice = (uint8_t) Services::ID::Servo2;
    uint8_t Pyroservice = (uint8_t) Services::ID::Pyro;
    uint8_t ChamberPTservice = (uint8_t) Services::ID::PT0;
    uint8_t OxPTservice = (uint8_t) Services::ID::PT1;
    uint8_t FuelPTservice = (uint8_t) Services::ID::PT2;



    Types::EngineTypes::StateMachine_t _engineStateMachine;
    Types::EngineTypes::SystemStatus_t _engineStatus;

    Engine::DefaultStateInit m_DefaultStateParams = {_engineStatus, OxMainAdapter, FuelMainAdapter, PyroAdapter};
    Engine::IgnitionStateInit m_IgnitionStateParams = {_engineStatus, PyroAdapter};
    Engine::ControlledStateInit m_ControlledStateParams = {_engineStatus, OxMainAdapter, FuelMainAdapter};
    Engine::ShutdownStateInit m_ShutdownStateParams = {_engineStatus, OxMainAdapter, FuelMainAdapter};


    // uint32_t _OxAngle;
    // uint32_t _FuelAngle;

    uint32_t getOxAngle();
    uint32_t getFuelAngle();
    protected:

    friend class NRCRemoteActuatorBase;
    friend class NRCRemoteBase;


};


    


