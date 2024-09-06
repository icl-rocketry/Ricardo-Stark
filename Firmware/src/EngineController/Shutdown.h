#pragma once

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include "enginetypes.h"
#include "enginecontroller.h"

class Shutdown: public Types::EngineTypes ::State_t
{
    public:

    Shutdown(Engine::ShutdownStateInit& ShutdownInitParams);

    void initialize() override;

    Types::EngineTypes::State_ptr_t update() override;

    void exit() override;


    private:

    Types::LocalServoAdapter_t& _OxMainAdapter;
    Types::LocalServoAdapter_t& _FuelMainAdapter;
   
  
   

};