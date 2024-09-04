// #include "Ignition.h"

// #include <memory>

// #include <libriccore/fsm/state.h>
// #include <libriccore/systemstatus/systemstatus.h>
// #include <libriccore/commands/commandhandler.h>
// #include <libriccore/riccorelogging.h>

// #include "Config/systemflags_config.h"
// #include "Config/types.h"
// #include "Config/commands_config.h"

// #include "system.h"
// #include "Engine.h"

// Ignition::Ignition(System &system, Engine &engine): State(SYSTEM_FLAG::STATE_IGNITION, system.systemstatus),
//                                     _system(system),
//                                     _engine(system.ThanosR)
//                                     {};

// void Ignition::initialize()
// {
//     State::initialize();

//     _system.commandhandler.enableCommands({
//         Commands::ID::Shutdown
//         });

//     _engine._networkmanager.registerService(_engine.Pyroservice,_engine.Pyro.getThisNetworkCallback());

//     m_IgnitionCalls = 0; //Initialise Ignition calls

// };


// Types::CoreTypes::State_ptr_t Ignition::update()
// {

// // Check ignition calls and fire pyro accordingly

// if (m_IgnitionCalls > 0) //Ignition has been called already
// {
//     if(millis() - m_ignitionTime < m_pyroTime)
//     {
//         return nullptr;
//     }
//     else
//     {
//         _engine._networkmanager.unregisterService(_engine.Pyroservice);
//         return std::make_unique<Controlled>(_engine);
//     }
  
// }

// else if (m_IgnitionCalls == 0)
// {
    
//     _engine.PyroAdapter.execute(5000);
//     m_ignitionTime = millis();
//     m_IgnitionCalls++;

//     return nullptr;
// }

// };

// void Ignition::exit()
// {
//     State::exit();
//     _system.commandhandler.resetCommands();
// };