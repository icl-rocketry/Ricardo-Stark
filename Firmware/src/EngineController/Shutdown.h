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

    Shutdown(Engine::DefaultStateInit& DefaultInitParams, RnpNetworkManager& networkmanager, EngineController& Engine);

    void initialize() override;

    Types::EngineTypes::State_ptr_t update() override;

    void exit() override;


    private:

    RnpNetworkManager& _networkmanager;
    EngineController& _engine;
    
    Types::LocalServoAdapter_t& _OxMainAdapter;
    Types::LocalServoAdapter_t& _FuelMainAdapter;

    uint8_t m_ereg_service = 10; //Update
    uint8_t m_ereg_address = 0; //Update
   
  
   

};