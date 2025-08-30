#include "enginecontroller.h"
#include <math.h>
#include <Arduino.h>

#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>

#include "Deployment/PCA9534.h"
#include "Deployment/PCA9534Gpio.h"


#include "Default.h"
#include "Armed.h"
#include "Ignition.h"
#include "Controlled.h"
#include "Shutdown.h"
#include "Debug.h"

#include "EngineController/Control/throttle.h"

 

EngineController::EngineController(RnpNetworkManager& networkmanager, SensorHandler& sensorHandler, PCA9534& pyroPinExpander):
                    NRCRemoteActuatorBase(networkmanager),
                    _networkmanager(networkmanager),  
                    _sensorHandler(sensorHandler),
                    OxMain(LocalPWM(PinMap::ServoPWM1), networkmanager,"OxMain"),
                    OxMainAdapter(0,OxMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    FuelMain(LocalPWM(PinMap::ServoPWM2),networkmanager,"FuelMain"),
                    FuelMainAdapter(0,FuelMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
                    Pyro(ArduinoGpio(PinMap::PyroNuke), PCA9534Gpio(pyroPinExpander,PinMap::PyroCont), _networkmanager),
                    PyroAdapter(0,Pyro,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);})

{}; 


void EngineController::setup()
{

    OxMain.setup();
    FuelMain.setup();
    Pyro.setup();

    serviceSetup();

     // Abort GPIO
     pinMode(PinMap::Abort,INPUT_PULLDOWN);

    _engineStateMachine.initalize(std::make_unique<Default>(m_DefaultStateParams, *this));

}

void EngineController::update()
{   
    _value = _engineStatus.getStatus();
    _engineStateMachine.update();


};

void EngineController::arm_base(int32_t arg){


    PyroAdapter.arm(arg);
    OxMainAdapter.arm(arg);
    FuelMainAdapter.arm(arg);

    if (PyroAdapter.getState().flagSet(LIBRRC::COMPONENT_STATUS_FLAGS::NOMINAL)&& 
        OxMainAdapter.getState().flagSet(LIBRRC::COMPONENT_STATUS_FLAGS::NOMINAL)&&
        FuelMainAdapter.getState().flagSet(LIBRRC::COMPONENT_STATUS_FLAGS::NOMINAL))
            {

                NRCRemoteActuatorBase::arm_base(arg);

                if (this->_state.flagSet(LIBRRC::COMPONENT_STATUS_FLAGS::NOMINAL) && _engineStateMachine.getCurrentStateID() == EC_FLAGS::State_Default)
                
                _engineStateMachine.changeState(std::make_unique<Armed>(m_DefaultStateParams, _networkmanager, *this));

            }
    else {

        PyroAdapter.disarm();
        OxMainAdapter.disarm();
        FuelMainAdapter.disarm();
    }

    

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

float EngineController::getOF()
{
    return m_currOF;
}

float EngineController::getFuelCalc(){

    return m_fuelcalc;
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
             if (!_engineStatus.flagSet(EC_FLAGS::ARMED))
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






