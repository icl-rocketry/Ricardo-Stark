#pragma once

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include "enginetypes.h"

#include "enginecontroller.h"

class Ignition: public Types::EngineTypes ::State_t
{
    public:

    Ignition(Engine::IgnitionStateInit& IgnitionInitParams, Engine::ControlledStateInit& ControlledInitParams, EngineController& Engine);

    void initialize() override;

    Types::EngineTypes::State_ptr_t update() override;

    void exit() override;


    private:

    Engine::ControlledStateInit& m_ControlledInitParams;
    EngineController& _engine;
    Types::LocalPyroAdapter_t& _PyroAdapter;

    

    uint8_t m_IgnitionCalls;
    uint64_t m_ignitionTime;
    uint64_t m_pyroTime = 500; 
   
   
  
   

};