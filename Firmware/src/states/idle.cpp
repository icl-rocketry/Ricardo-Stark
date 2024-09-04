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

// Idle::Idle(System &system, Engine &engine): State(SYSTEM_FLAG::STATE_IDLE, system.systemstatus),
//                                     _system(system),
//                                     _engine(system.ThanosR)
//                                     {};

// void Idle::initialize()
// {
//     State::initialize();

//     _system.commandhandler.enableCommands({
//         Commands::ID::Ignition,
//         Commands::ID::Debug
//         });

// // Unregistering services so they can only be accessed in debug mode

//     _engine._networkmanager.unregisterService(_engine.OxMainservice);
//     _engine._networkmanager.unregisterService(_engine.FuelMainservice);
//     _engine._networkmanager.unregisterService(_engine.Pyroservice);
//     _engine._networkmanager.unregisterService(_engine.ChamberPTservice);
//     _engine._networkmanager.unregisterService(_engine.OxPTservice);
//     _engine._networkmanager.unregisterService(_engine.FuelPTservice);
// };
// Types::CoreTypes::State_ptr_t Idle::update()
// {

// return nullptr;

// };

// void Idle::exit()
// {
//     State::exit();
//     _system.commandhandler.resetCommands();
// };