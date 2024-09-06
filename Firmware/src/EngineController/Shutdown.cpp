#include "Shutdown.h"

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include <librrc/Local/remoteactuatoradapter.h> 

#include "system.h"

Shutdown::Shutdown(Engine::ShutdownStateInit& ShutdownInitParams):
State(EC_FLAGS::SHUTDOWN,ShutdownInitParams.enginestatus),
_OxMainAdapter(ShutdownInitParams.OxAdapter),
_FuelMainAdapter(ShutdownInitParams.FuelAdapter)
{};

void Shutdown::initialize()
{
    Types::EngineTypes::State_t::initialize();

    _OxMainAdapter.arm(0); 
    _FuelMainAdapter.arm(0);

    _OxMainAdapter.execute(180);
    _FuelMainAdapter.execute(0);

    _OxMainAdapter.disarm();
    _FuelMainAdapter.disarm();
  
  
};

Types::EngineTypes::State_ptr_t Shutdown::update()
{

    digitalWrite(PinMap::LED, HIGH);
    return nullptr;

    

}

void Shutdown::exit()
{
    Types::EngineTypes::State_t::exit();
};