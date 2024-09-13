#pragma once

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include "enginetypes.h"
#include "enginecontroller.h"

class Default: public Types::EngineTypes ::State_t
{
    public:

    Default(Engine::DefaultStateInit& DefaultInitParams, EngineController& Engine);

    void initialize() override;

    Types::EngineTypes::State_ptr_t update() override;

    void exit() override;


    private:

    EngineController& _engine; 
    Types::LocalServoAdapter_t& _OxMainAdapter;
    Types::LocalServoAdapter_t& _FuelMainAdapter;
   
  
   

};