#include "Ignition.h"

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include <librrc/Local/remoteactuatoradapter.h>

#include "system.h"

Ignition::Ignition(Engine::IgnitionStateInit& IgnitionInitParams, Engine::ControlledStateInit& ControlledInitParams, EngineController& Engine):
State(EC_FLAGS::IGNITION,IgnitionInitParams.enginestatus),
m_ControlledInitParams(ControlledInitParams),
_engine(Engine),
_PyroAdapter(IgnitionInitParams.PyroAdapter)

{};

void Ignition::initialize()
{
    Types::EngineTypes::State_t::initialize();

    _PyroAdapter.arm(0); 

    m_IgnitionCalls = 0; //Initialise Ignition calls
    m_ignitionTime = millis();
   
  
  
};

Types::EngineTypes::State_ptr_t Ignition::update()
{

// Check ignition calls and fire pyro accordingly

if (m_IgnitionCalls > 0) //Ignition has been called already
{
    if(millis() - m_ignitionTime < m_pyroTime)
    {
        return nullptr;
    }
    else
    {
        
        return std::make_unique<Controlled>(m_ControlledInitParams);
    }
  
}

else if (m_IgnitionCalls == 0)
{
    
    _engine.PyroAdapter.execute(5000);
    m_IgnitionCalls++;

    return nullptr;
}

    
}

void Ignition::exit()
{
    Types::EngineTypes::State_t::exit();
};