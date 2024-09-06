/**
 * @file types.h
 * @author Kiran de Silva (kd619@ic.ac.uk)
 * @brief type declarations for more convient types
 * @version 0.1
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#pragma once

#include <libriccore/riccoretypes.h>

//we need the forward declarations for the system aswell
#include "forward_decl.h"

#include "systemflags_config.h"
#include "commands_config.h"

#include <librrc/Remote/nrcremotepyro.h>
#include <librrc/Remote/nrcremoteservo.h>
#include <librrc/Remote/nrcremoteptap.h>

#include <librrc/HAL/localpwm.h>
#include <librrc/HAL/arduinogpio.h>

#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/fsm/state.h>
#include <libriccore/fsm/statemachine.h>

#include "EngineController/enginecontroller.h"


namespace Types{
    using CoreTypes = RicCoreTypes<ForwardDecl_SystemClass,SYSTEM_FLAG,Commands::ID,256>;
    //any other useful aliases used in multiple places should be defined here
    // using LocalServo_t = NRCRemoteServo<LocalPWM>;
    // using LocalPyro_t = NRCRemotePyro<ArduinoGpio>;
    // using LocalSensor_t = NRCRemotePTap;

    // using ServoAdapter_t = RemoteActuatorAdapter<LocalServo_t>;
    // using PyroAdapter_t = RemoteActuatorAdapter<LocalPyro_t>;
    // using SensorAdapter_t = RemoteSensorAdapter<LocalSensor_t>;
    // using LocalServoMap_t = std::array<LocalServo_t*,2>;
   
};

