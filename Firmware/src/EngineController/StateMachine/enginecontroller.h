#pragma once

#include <libriccore/fsm/statemachine.h>
#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <librrc/Remote/nrcremoteactuatorbase.h>
#include <librrc/Local/remoteactuatoradapter.h>

#include <librrc/HAL/localpwm.h>

#include <librnp/rnp_networkmanager.h>
#include <librnp/rnp_packet.h>

#include "config/types.h"
#include "config/pinmap_config.h"
#include "config/services_config.h"
#include "Sensors/ADS131M06.h"

#include <librrc/Remote/nrcremoteservo.h>
#include <librrc/Remote/nrcremotepyro.h>

#include "EngineTypes.h"
#include "Sensors/sensorHandler.h"




class EngineController: public NRCRemoteActuatorBase<EngineController>
{   
    
    public:

    EngineController(RnpNetworkManager& networkmanager, SensorHandler& _sensorHandler);

    void setup();
    void update();

    void arm_base(int32_t arg);
    void disarm_base();
    void execute_base(int32_t arg);

    void serviceSetup();
    void unregisterServices();

    void ignition(packetptr_t packetptr);
    void shutdown(packetptr_t packetptr);


    uint32_t telemetry_log_delta = 5000;
    uint32_t prev_telemetry_log_time;
    uint32_t prevtime;

 
    RnpNetworkManager& _networkmanager;
    SensorHandler& _sensorHandler;


    // Local Actuators

    Types::LocalServo_t OxMain;
    Types::LocalServoAdapter_t OxMainAdapter;

    Types::LocalServo_t FuelMain;
    Types::LocalServoAdapter_t FuelMainAdapter;

    Types::LocalPyro_t Pyro;
    Types::LocalPyroAdapter_t PyroAdapter;


    uint8_t OxMainservice = (uint8_t) Services::ID::Servo1;
    uint8_t FuelMainservice = (uint8_t) Services::ID::Servo2;
    uint8_t Pyroservice = (uint8_t) Services::ID::Pyro;

    

    Types::EngineTypes::StateMachine_t _engineStateMachine;
    Types::EngineTypes::SystemStatus_t _engineStatus;

    Engine::DefaultStateInit m_DefaultStateParams = {_engineStatus, OxMainAdapter, FuelMainAdapter, PyroAdapter};


    uint32_t getOxAngle();
    uint32_t getFuelAngle();


    protected:

    friend class NRCRemoteActuatorBase;
    friend class NRCRemoteBase;


};


    


