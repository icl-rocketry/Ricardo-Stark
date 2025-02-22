#include "Controlled.h"

#include <memory>

#include <libriccore/fsm/state.h>
#include <libriccore/systemstatus/systemstatus.h>
#include <libriccore/commands/commandhandler.h>
#include <libriccore/riccorelogging.h>

#include "Config/systemflags_config.h"
#include "Config/types.h"
#include <librrc/Local/remoteactuatoradapter.h> 

#include "system.h"
#include "Shutdown.h"

Controlled::Controlled(Engine::DefaultStateInit& DefaultInitParams,RnpNetworkManager& networkmanager, EngineController& Engine):
State(EC_FLAGS::CONTROLLED,DefaultInitParams.enginestatus),
m_DefaultInitParams(DefaultInitParams),
_networkmanager(networkmanager),
_engine(Engine),
_OxMainAdapter(DefaultInitParams.OxAdapter),
_FuelMainAdapter(DefaultInitParams.FuelAdapter),
m_throttle(Engine),
m_OF(Engine)
{};

void Controlled::initialize()
{
    Types::EngineTypes::State_t::initialize();

    _OxMainAdapter.arm(0); 
    _FuelMainAdapter.arm(0);

    _engine.OxMain.setAngleLims(m_throttleOx_min, m_OxAngleLim);
    _engine.FuelMain.setAngleLims(m_throttleFuel_min, m_FuelAngleLim); 

    m_Controlled_Command_time = millis();

    m_OxThrottleRange = m_OxAngleLim - m_throttleOx_min;
    m_FuelThrottleRange = m_FuelAngleLim - m_throttleFuel_min;

    m_throttle.setup(m_Controlled_Command_time);
    m_OF.setup();

    // Initialise time index
    m_timeIndex = 0;

  
};

Types::EngineTypes::State_ptr_t Controlled::update()
{

    updateThrottle();
    updateOF();
    

    if (millis() - m_Controlled_Command_time > m_Controlled_duration){

        return std::make_unique<Shutdown>(m_DefaultInitParams, _networkmanager, _engine);

    }

    //  if (digitalRead(PinMap::Abort)==LOW){

    //     return std::make_unique<Shutdown>(m_DefaultInitParams, _networkmanager, _engine);

    // }

    
        //Obtains valve angles from array
    
    if (millis() - m_Controlled_Command_time > time_array[m_timeIndex+1]){

        if (time_array.size() - 1 > m_timeIndex){

            m_timeIndex++;

        }  
    }


    if (millis() - m_Controlled_Command_time > m_OxDelay){

        _OxMainAdapter.execute(m_OxAngle[m_timeIndex]);
        // _OxMainAdapter.execute(_nextOxAngle);
    }

    if (millis() - m_Controlled_Command_time > m_FuelDelay){

        _FuelMainAdapter.execute(m_FuelAngle[m_timeIndex]);
        // _FuelMainAdapter.execute(_nextFuelAngle);

    }

        return nullptr;

    }

void Controlled::updateThrottle(){

    m_throttle.update();
    _nextOxAngle = m_throttle.getNextAngle();


}

void Controlled::updateOF(){

    m_OF.update();
    _engine.m_currOF = m_OF.getOF();
    _engine.m_fuelcalc = m_OF.getCalcFuelFlow();
    _nextFuelAngle = m_OF.getNextAngle();

}
    

void Controlled::exit()
{
    Types::EngineTypes::State_t::exit();
};



