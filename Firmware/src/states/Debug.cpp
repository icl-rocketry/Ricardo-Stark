// #include "Debug.h"
// #include "Config/services_config.h"
// #include <libriccore/riccoresystem.h>
// #include <librrc/Remote/nrcremoteservo.h>
// #include <librrc/Remote/nrcremoteptap.h>
// #include <librrc/Remote/nrcremoteptap.h>


// Debug::Debug(System &system, Engine &engine): State(SYSTEM_FLAG::STATE_DEBUG, system.systemstatus),
//                                     _system(system),
//                                     _engine(system.ThanosR)
//                                     {};



// void Debug::initialize()
// {
//     State::initialize();

//     _system.commandhandler.enableCommands({

//         Commands::ID::Idle
//         });

//     _engine._networkmanager.registerService(_engine.OxMainservice,_engine.OxMain.getThisNetworkCallback());
//     _engine._networkmanager.registerService(_engine.FuelMainservice, _engine.FuelMain.getThisNetworkCallback());
//     _engine._networkmanager.registerService(_engine.Pyroservice,_engine.Pyro.getThisNetworkCallback());
//     _engine._networkmanager.registerService(_engine.ChamberPTservice,_engine.ChamberPT.getThisNetworkCallback());
//     _engine._networkmanager.registerService(_engine.OxPTservice,_engine.OxPT.getThisNetworkCallback());
//     _engine._networkmanager.registerService(_engine.FuelPTservice,_engine.FuelPT.getThisNetworkCallback());

// };

// Types::CoreTypes::State_ptr_t Debug::update()
// {

// return nullptr;   

// };

// void Debug::exit()
// {
//     State::exit();

//     _system.commandhandler.resetCommands();
// };