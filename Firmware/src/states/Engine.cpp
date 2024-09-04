// #include "Engine.h"


// EngineController::EngineController(RnpNetworkManager &networkmanager, ADS131M06 &ADC): 
//                     NRCRemoteActuatorBase(_networkmanager),
//                     _networkmanager(networkmanager),
//                     ADC(ADC),
//                     OxMain(LocalPWM(PinMap::ServoPWM1,0), _networkmanager,std::string("OxMain")),
//                     OxMainAdapter(0,OxMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
//                     FuelMain(LocalPWM(PinMap::ServoPWM2,1),_networkmanager,std::string("FuelMain")),
//                     FuelMainAdapter(0,FuelMain,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
//                     Pyro(PinMap::PyroNuke, PinMap::PyroCont, _networkmanager),
//                     PyroAdapter(0,Pyro,[](const std::string& msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);}),
//                     ChamberPT(_networkmanager, 0, 0),
//                     OxPT(_networkmanager, 1, 1),
//                     FuelPT(_networkmanager, 2, 2)  
                    
// {};

// void EngineController::setup()
// {
//     OxMain.setup();
//     FuelMain.setup();

//     OxMain.setAngleLims(0,m_OxAngleLim);
//     FuelMain.setAngleLims(0,m_FuelAngleLim);

//     Pyro.setup();
//     ChamberPT.setup();
//     OxPT.setup();
//     FuelPT.setup();

//     EngineStateMachine.changeState(std::make_unique<Idle>());


// };

// void EngineController::update()
// {   
//     ChamberPT.update(ADC.getOutput(0));
//     OxPT.update(ADC.getOutput(1));
//     FuelPT.update(ADC.getOutput(2));

//     logReadings();

// };


// void EngineController::logReadings()
// {
//     if (micros() - prev_telemetry_log_time > telemetry_log_delta)
//     {
//         TelemetryLogframe logframe;
 
//         logframe.ch0sens = ChamberPT.getPressure();
//         logframe.ch1sens = OxPT.getPressure();
//         logframe.ch2sens = FuelPT.getPressure();

//         logframe.timestamp = micros();

//         RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::TELEMETRY>(logframe);

//         prev_telemetry_log_time = micros();
//     }
// };

// void EngineController::arm_impl()
// {
//     _networkmanager.registerService(OxMainservice,OxMain.getThisNetworkCallback());
//     _networkmanager.registerService(FuelMainservice,FuelMain.getThisNetworkCallback());
//     _networkmanager.registerService(Pyroservice,Pyro.getThisNetworkCallback());

//     PyroAdapter.arm(0);
//     OxMainAdapter.arm(0);
//     FuelMainAdapter.arm(0);

//     _networkmanager.unregisterService(OxMainservice);
//     _networkmanager.unregisterService(FuelMainservice);
//     _networkmanager.unregisterService(Pyroservice);
    
// };

// void EngineController::disarm_impl()
// {   
//     _networkmanager.registerService(OxMainservice,OxMain.getThisNetworkCallback());
//     _networkmanager.registerService(FuelMainservice,FuelMain.getThisNetworkCallback());
//     _networkmanager.registerService(Pyroservice,Pyro.getThisNetworkCallback());

//     PyroAdapter.disarm();
//     OxMainAdapter.disarm();
//     FuelMainAdapter.disarm();

//     _networkmanager.unregisterService(OxMainservice);
//     _networkmanager.unregisterService(FuelMainservice);
//     _networkmanager.unregisterService(Pyroservice);
// };



