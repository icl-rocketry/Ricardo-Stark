#include "Default.h"

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include <librrc/Local/remoteactuatoradapter.h> 

#include "system.h"

Default::Default(Engine::DefaultStateInit& DefaultInitParams, EngineController& Engine):
State(EC_FLAGS::State_Default,DefaultInitParams.enginestatus),
_engine(Engine),
_OxMainAdapter(DefaultInitParams.OxAdapter),
_FuelMainAdapter(DefaultInitParams.FuelAdapter)
{};

void Default::initialize()
{
    Types::EngineTypes::State_t::initialize();

    _OxMainAdapter.arm(0); 
    _FuelMainAdapter.arm(0);

    _engine.OxMain.setAngleLims(0, 180);
    _engine.FuelMain.setAngleLims(0, 180);
    
    _OxMainAdapter.execute(0);
    _FuelMainAdapter.execute(0);

    _OxMainAdapter.disarm();
    _FuelMainAdapter.disarm();
  
  
};

Types::EngineTypes::State_ptr_t Default::update()
{

    digitalWrite(PinMap::LED, HIGH);
    
    return nullptr;

    

}

void Default::exit()
{
    Types::EngineTypes::State_t::exit();
};