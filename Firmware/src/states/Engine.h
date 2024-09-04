// #pragma once

// #include <libriccore/fsm/state.h>
// #include <libriccore/systemstatus/systemstatus.h>
// #include <libriccore/commands/commandhandler.h>
// #include <libriccore/riccoresystem.h>
// #include <librrc/Remote/nrcremoteactuatorbase.h>
// #include <librrc/Local/remoteactuatoradapter.h>
// #include "config/systemflags_config.h"
// #include "config/types.h"
// #include "config/pinmap_config.h"
// #include "config/services_config.h"
// #include <libriccore/fsm/statemachine.h>
// #include <librrc/HAL/localpwm.h>
// #include "config/forward_decl.h"
// #include "Sensors/ADS131M06.h"


// #include "idle.h"
// #include "Ignition.h"
// #include "Controlled.h"
// #include "Shutdown.h"
// #include "Debug.h"

// #include <librrc/Remote/nrcremoteservo.h>
// #include <librrc/Remote/nrcremoteptap.h>
// #include <librrc/Remote/nrcremotepyro.h>

// #include "system.h"

// class EngineController : public NRCRemoteActuatorBase<EngineController>{

//     friend class Idle;
//     friend class Ignition;
//     friend class Controlled;
//     friend class Shutdown;
//     friend class Debug;


//     public:
    
//     EngineController(RnpNetworkManager& networkmanager, ADS131M06& ADC);

//     void setup();
//     void serviceSetup();            
//     void update();
//     void logReadings();

//     void arm_impl();
//     void disarm_impl();



//     private:

//     uint8_t OxMainservice = (uint8_t) Services::ID::Servo1;
//     uint8_t FuelMainservice = (uint8_t) Services::ID::Servo2;
//     uint8_t Pyroservice = (uint8_t) Services::ID::Pyro;
//     uint8_t ChamberPTservice = (uint8_t) Services::ID::PT0;
//     uint8_t OxPTservice = (uint8_t) Services::ID::PT1;
//     uint8_t FuelPTservice = (uint8_t) Services::ID::PT2;

//     uint16_t m_OxAngleLim = 175;
//     uint16_t m_FuelAngleLim = 160;

//     RnpNetworkManager& _networkmanager;
//     ADS131M06& ADC;

//     Types::LocalServo_t OxMain;
//     RemoteActuatorAdapter<Types::LocalServo_t> OxMainAdapter;
//     Types::LocalServo_t FuelMain;
//     RemoteActuatorAdapter<Types::LocalServo_t> FuelMainAdapter;

//     Types::LocalPyro_t Pyro;
//     RemoteActuatorAdapter<ArduinoGpio> PyroAdapter;

//     SystemStatus<SYSTEM_FLAG> enginestatus;

//     StateMachine<SYSTEM_FLAG> EngineStateMachine;


//     uint32_t telemetry_log_delta = 5000;
//     uint32_t prev_telemetry_log_time;
//     uint32_t prevtime;

//     public:

//     NRCRemotePTap ChamberPT;
//     NRCRemotePTap OxPT;
//     NRCRemotePTap FuelPT;



// };