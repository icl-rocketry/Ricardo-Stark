#pragma once
#include <cstdint>
#include <memory>

#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/fsm/state.h>
#include <libriccore/fsm/statemachine.h>


enum class EC_FLAGS:uint8_t{

    State_Default =(1<<0),
    IGNITION = (3 << 0),
    CONTROLLED = (4 <<0),
    SHUTDOWN = (5 << 0),
    DEBUG = (6 << 0)
};


template <typename EC_FLAGS_T>
struct ECTypes
{
    using SystemStatus_t = SystemStatus<EC_FLAGS_T>;
    using State_t = State<EC_FLAGS_T>;
    using State_ptr_t = std::unique_ptr<State_t>;
    using StateMachine_t = StateMachine<EC_FLAGS_T>;
};

namespace Types
{
    using EngineTypes = ECTypes<EC_FLAGS>;
    using LocalServo_t = NRCRemoteServo<LocalPWM>;
    using LocalServoAdapter_t = RemoteActuatorAdapter<Types::LocalServo_t>;
    using LocalServoAdapterMap_t = std::array<LocalServoAdapter_t *, 2>;

    using LocalPyro_t = NRCRemotePyro<ArduinoGpio>;
    using LocalPyroAdapter_t = RemoteActuatorAdapter<Types::LocalPyro_t>;
    using LocalPyroMap_t = std::array<LocalPyroAdapter_t *, 1>;
};

namespace Engine
{
    struct DefaultStateInit
    {
        Types::EngineTypes::SystemStatus_t &enginestatus;
        Types::LocalServoAdapter_t &OxAdapter;
        Types::LocalServoAdapter_t &FuelAdapter;
        
    };

    struct IgnitionStateInit
    {
        Types::EngineTypes::SystemStatus_t &enginestatus;
        Types::LocalPyroAdapter_t &PyroAdapter;
        
    };
    
      struct ControlledStateInit
    {
        Types::EngineTypes::SystemStatus_t &enginestatus;
        Types::LocalServoAdapter_t &OxAdapter;
        Types::LocalServoAdapter_t &FuelAdapter;
   
        
    };

        struct ShutdownStateInit
    {
        Types::EngineTypes::SystemStatus_t &enginestatus;
        Types::LocalServoAdapter_t &OxAdapter;
        Types::LocalServoAdapter_t &FuelAdapter;
        
    };
    
}