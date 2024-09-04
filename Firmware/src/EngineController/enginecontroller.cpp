#include "enginecontroller.h"


EngineController::EngineController(RnpNetworkManager& networkmanager):
                    NRCRemoteActuatorBase(_networkmanager),
                    _networkmanager(networkmanager),
                    EC_statemachine(),
                    OxMain(LocalPWM(PinMap::ServoPWM1,0), _networkmanager,std::string("OxMain")),
                    OxMainAdapter(0,OxMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    FuelMain(LocalPWM(PinMap::ServoPWM2,1),_networkmanager,std::string("FuelMain")),
                    FuelMainAdapter(0,FuelMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    Pyro(PinMap::PyroNuke, PinMap::PyroCont, _networkmanager),
                    PyroAdapter(0,Pyro,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    ChamberPT(_networkmanager, 0, 0),
                    ChamberPTAdapter(0,ChamberPT,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    OxPT(_networkmanager, 1, 1),
                    OxPTAdapter(0,OxPT,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    FuelPT(_networkmanager, 2, 2),
                    FuelPTAdapter(0,FuelPT,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);})  

{}; 


void EngineController::armEngine(packetptr_t packetptr){

    SimpleCommandPacket execute_command(*packetptr);

    if (execute_command.command == 3){

        PyroAdapter.arm(0);
        OxMainAdapter.arm(0);
        FuelMainAdapter.arm(0);
    }

}


void EngineController::disarmEngine(packetptr_t packetptr){

    SimpleCommandPacket execute_command(*packetptr);

    if (execute_command.command == 4){

        PyroAdapter.disarm();
        OxMainAdapter.disarm();
        FuelMainAdapter.disarm();
    }

}

void EngineController::serviceSetup(){

    _networkmanager.registerService(OxMainservice,OxMain.getThisNetworkCallback());
    _networkmanager.registerService(FuelMainservice,FuelMain.getThisNetworkCallback());
    _networkmanager.registerService(Pyroservice,Pyro.getThisNetworkCallback());


}

void EngineController::ignition(packetptr_t packetptr){

    SimpleCommandPacket execute_command(*packetptr);

    if (execute_command.arg == 1){

        EC_statemachine.changeState(std::make_unique<IGNITION>(EC_statemachine));

    }

}




