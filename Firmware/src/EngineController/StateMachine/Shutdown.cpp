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

Shutdown::Shutdown(Engine::DefaultStateInit& DefaultInitParams, RnpNetworkManager& networkmanager, EngineController& Engine):
State(EC_FLAGS::SHUTDOWN,DefaultInitParams.enginestatus),
_networkmanager(networkmanager),
_engine(Engine),
_OxMainAdapter(DefaultInitParams.OxAdapter),
_FuelMainAdapter(DefaultInitParams.FuelAdapter)
{};

void Shutdown::initialize()
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

    // Kills nitrogen pressurisation when engine shuts down

    SimpleCommandPacket n2_shutdown(2, 2);
    n2_shutdown.header.source_service = static_cast<uint8_t>(Services::ID::Engine);
    n2_shutdown.header.destination_service = 10;
    n2_shutdown.header.source = 1;
    n2_shutdown.header.destination = 9;
    n2_shutdown.header.uid = 0;
    _networkmanager.sendPacket(n2_shutdown);
};

Types::EngineTypes::State_ptr_t Shutdown::update()
{
   
    return nullptr;

}

void Shutdown::exit()
{
    Types::EngineTypes::State_t::exit();
};