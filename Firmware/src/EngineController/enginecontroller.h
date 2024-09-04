#include <libriccore/fsm/statemachine.h>
#include <libriccore/fsm/state.h>
#include <librrc/Remote/nrcremoteactuatorbase.h>
#include <librrc/Local/remoteactuatoradapter.h>
#include <librrc/Local/remotesensoradapter.h>

#include <librnp/rnp_networkmanager.h>
#include <librnp/rnp_packet.h>

#include "config/types.h"
#include "config/pinmap_config.h"
#include "config/services_config.h"

#include <librrc/Remote/nrcremoteservo.h>
#include <librrc/Remote/nrcremoteptap.h>
#include <librrc/Remote/nrcremotepyro.h>


enum class EC_FLAGS:uint8_t{
    IDLE =(1<<0),
    IGNITION = (3 << 0),
    CONTROLLED = (4 <<0),
    SHUTDOWN = (5 << 0)
};


class EngineController: public NRCRemoteActuatorBase<EngineController>
{   
    
    public:

    using EC_State_T = State<EC_FLAGS>;
    using EC_StateMachine_T = StateMachine<EC_FLAGS>;

    EngineController(RnpNetworkManager& networkmanager);


    private:

    void setup();
    void update();

    void extendedCommandHandler_impl(const NRCPacket::NRC_COMMAND_ID commandID, packetptr_t packetptr);


    void armEngine(packetptr_t packetptr);
    void disarmEngine(packetptr_t packetptr);
    void serviceSetup();

    void ignition(packetptr_t packetptr);
    void shutdown(packetptr_t packetptr);

    
    RnpNetworkManager& _networkmanager;
    
    StateMachine<EC_FLAGS> EC_statemachine;


    Types::LocalServo_t OxMain;
    RemoteActuatorAdapter<Types::LocalServo_t> OxMainAdapter;
    Types::LocalServo_t FuelMain;
    RemoteActuatorAdapter<Types::LocalServo_t> FuelMainAdapter;
    Types::LocalPyro_t Pyro;
    RemoteActuatorAdapter<ArduinoGpio> PyroAdapter;

    NRCRemotePTap ChamberPT;
    RemoteSensorAdapter<Types::LocalSensor_t> ChamberPTAdapter;
    NRCRemotePTap OxPT;
    RemoteSensorAdapter<Types::LocalSensor_t> OxPTAdapter;
    NRCRemotePTap FuelPT;
    RemoteSensorAdapter<Types::LocalSensor_t> FuelPTAdapter;


    uint8_t OxMainservice = (uint8_t) Services::ID::Servo1;
    uint8_t FuelMainservice = (uint8_t) Services::ID::Servo2;
    uint8_t Pyroservice = (uint8_t) Services::ID::Pyro;
    uint8_t ChamberPTservice = (uint8_t) Services::ID::PT0;
    uint8_t OxPTservice = (uint8_t) Services::ID::PT1;
    uint8_t FuelPTservice = (uint8_t) Services::ID::PT2;

};


class EC_Idle :public EngineController::EC_State_T
{
    
};
