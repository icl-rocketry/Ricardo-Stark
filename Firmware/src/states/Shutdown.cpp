// #include "Shutdown.h"



// Shutdown::Shutdown(System &system, EngineController& engine): State(SYSTEM_FLAG::STATE_SHUTDOWN, system.systemstatus),
//                                     _system(system),
//                                     _engine(system.ThanosR)
//                                     {};

// void Shutdown::initialize()
// {
//     State::initialize();

// };

// Types::CoreTypes::State_ptr_t Shutdown::update()
// {

//     _engine.OxMainAdapter.execute(0);
//     _engine.FuelMainAdapter.execute(_engine.m_FuelAngleLim);

//     if (_engine.enginestatus.flagSet(COMPONENT_STATUS_FLAGS::DISARMED)) //Move to idle when disarmed
//     {
//         return std::make_unique<Idle>(_engine);

//     } 

//     else{

//         return nullptr;
//     }

// };

// void Shutdown::exit()
// {
//     State::exit();
//     _system.commandhandler.resetCommands();
// };