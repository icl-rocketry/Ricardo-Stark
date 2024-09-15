#include "enginecontroller.h"
#include <math.h>
#include <Arduino.h>

#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>


#include "Default.h"
#include "Ignition.h"
#include "Controlled.h"
#include "Shutdown.h"
#include "Debug.h"

 

EngineController::EngineController(RnpNetworkManager& networkmanager, NRCRemotePTap& chamberPt, NRCRemotePTap& oxPt, NRCRemotePTap& oxInjPT):
                    NRCRemoteActuatorBase(networkmanager),
                    _networkmanager(networkmanager),    
                    _ChamberPT(chamberPt),
                    _OxPT(oxPt),
                    _OxInjPT(oxInjPT),
                    OxMain(LocalPWM(PinMap::ServoPWM1,0), networkmanager,"OxMain"),
                    OxMainAdapter(0,OxMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    FuelMain(LocalPWM(PinMap::ServoPWM2,1),networkmanager,"FuelMain"),
                    FuelMainAdapter(0,FuelMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    Pyro(PinMap::PyroNuke, PinMap::PyroCont, _networkmanager),
                    PyroAdapter(0,Pyro,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);})

{}; 


void EngineController::setup()
{

    OxMain.setup();
    FuelMain.setup();
    Pyro.setup();


    // Registering Actuator Services
    serviceSetup();


    _engineStateMachine.initalize(std::make_unique<Default>(m_DefaultStateParams, *this));




}

void EngineController::update()
{   
    _value = _engineStatus.getStatus();
    _engineStateMachine.update();
    logReadings();


};

void EngineController::arm_base(int32_t arg){


    PyroAdapter.arm(arg);
    OxMainAdapter.arm(arg);
    FuelMainAdapter.arm(arg);

     NRCRemoteActuatorBase::arm_base(arg);

}


void EngineController::disarm_base(){

    PyroAdapter.disarm();
    OxMainAdapter.disarm();
    FuelMainAdapter.disarm();

    NRCRemoteActuatorBase::disarm_base();

    _engineStateMachine.initalize(std::make_unique<Default>(m_DefaultStateParams, *this));



}

uint32_t EngineController::getOxAngle()
{
    return OxMain.getValue();
}

uint32_t EngineController::getFuelAngle()
{
    return FuelMain.getValue();
}


void EngineController::serviceSetup(){

    _networkmanager.registerService(OxMainservice,OxMain.getThisNetworkCallback());
    _networkmanager.registerService(FuelMainservice,FuelMain.getThisNetworkCallback());
    _networkmanager.registerService(Pyroservice,Pyro.getThisNetworkCallback());


}

void EngineController::unregisterServices(){

    _networkmanager.unregisterService(OxMainservice);
    _networkmanager.unregisterService(FuelMainservice);
    _networkmanager.unregisterService(Pyroservice);


}

void EngineController::execute_base(int32_t arg)
{

    switch(arg)
    {
        case 1:
        {   
             if (!_engineStatus.flagSet(EC_FLAGS::State_Default))
        {
            break;
        }
            // Ignition
            _engineStateMachine.changeState(std::make_unique<Ignition>(m_DefaultStateParams, _networkmanager, *this));

            break;

        }

        case 2:
        {
            // Shutdown
            _engineStateMachine.changeState(std::make_unique<Shutdown>(m_DefaultStateParams, _networkmanager, *this));

            break;  

        }

        case 3:
        {
            // Debug
            _engineStateMachine.changeState(std::make_unique<Debug>(m_DefaultStateParams, _networkmanager, *this));
            break;

        }

        case 4:
        {
            // Enter Default from Debug

            if(!_engineStatus.flagSet(EC_FLAGS::DEBUG))
            {
                break;
            }

             // Default
            _engineStateMachine.changeState(std::make_unique<Default>(m_DefaultStateParams, *this));

            break;


        }



    }

}

void EngineController::logReadings()
{
    if (micros() - prev_telemetry_log_time > telemetry_log_delta)
    {
        TelemetryLogframe logframe;

        logframe.ch0sens = _ChamberPT.getPressure();
        logframe.ch1sens = _OxPT.getPressure();
        logframe.ch2sens = _OxInjPT.getPressure();

        logframe.timestamp = micros();

        RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::TELEMETRY>(logframe);

        prev_telemetry_log_time = micros();
    }
}








