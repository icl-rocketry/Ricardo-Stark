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
_FuelMainAdapter(DefaultInitParams.FuelAdapter)
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

    // Initialise time index
    m_timeIndex = 0;

  
};

Types::EngineTypes::State_ptr_t Controlled::update()
{

   
    m_Pc = _engine._ChamberPT.getPressure();
    

    if (millis() - m_Controlled_Command_time > m_Controlled_duration){

        return std::make_unique<Shutdown>(m_DefaultInitParams, _networkmanager, _engine);

    }
    
        //Obtains valve angles from array
    
    if (millis() - m_Controlled_Command_time > time_array[m_timeIndex+1]){

        if (time_array.size() - 1 > m_timeIndex){

            m_timeIndex++;

        }  
    }
        _OxMainAdapter.execute(m_OxAngle[m_timeIndex]);
        _FuelMainAdapter.execute(m_FuelAngle[m_timeIndex]);

        return nullptr;

    }

    

void Controlled::exit()
{
    Types::EngineTypes::State_t::exit();
};



float Controlled::Fuel_FF(float OxAngle){

     m_OxPercent = (float)(_nextOxAngle -  m_throttleOx_min) / (float)(m_OxThrottleRange );

     m_FuelPercent = m_OxPercent + m_FuelExtra;
    
    float fuelAngle = (float)(m_FuelPercent * m_FuelThrottleRange) + m_throttleFuel_min;

    if (fuelAngle < m_throttleFuel_min)
    {
        fuelAngle = m_throttleFuel_min;
    }
    
    return fuelAngle;

}


