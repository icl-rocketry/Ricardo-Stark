#include "Armed.h"

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include <librrc/Local/remoteactuatoradapter.h> 

#include "system.h"

Armed::Armed(Engine::DefaultStateInit& DefaultInitParams, RnpNetworkManager& networkmanager, EngineController& Engine):
State(EC_FLAGS::ARMED,DefaultInitParams.enginestatus),
_networkmanager(networkmanager),
_engine(Engine),
_OxMainAdapter(DefaultInitParams.OxAdapter),
_FuelMainAdapter(DefaultInitParams.FuelAdapter),
_PyroAdapter(DefaultInitParams.PyroAdapter)
{};

void Armed::initialize()
{
    Types::EngineTypes::State_t::initialize();


    _engine.serviceSetup();
  
};

Types::EngineTypes::State_ptr_t Armed::update()
{
     
    return nullptr;

}

void Armed::exit()
{
    Types::EngineTypes::State_t::exit();
};