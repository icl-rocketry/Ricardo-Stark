#pragma once

#include <libriccore/riccoresystem.h>

#include <memory>
#include <librrc/Remote/nrcremoteservo.h>
#include <librrc/Remote/nrcremoteptap.h> 
#include <librrc/Remote/nrcremotepyro.h>
#include <librrc/Remote/nrcremotepotentiometer.h>

#include "Sensors/ADS131M06.h"
#include "SiC43x.h"


#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include <libriccore/networkinterfaces/can/canbus.h>
#include "config/pinmap_config.h"

#include "EngineController/StateMachine/enginecontroller.h"
#include "EngineController/StateMachine/Ignition.h"
#include "EngineController/StateMachine/Controlled.h"

#include "Sensors/sensorHandler.h"

#include "Commands/commands.h"

#include "Storage/sdfat_store.h"
#include "Storage/sdfat_file.h"

#include <SPI.h>
class System : public RicCoreSystem<System,SYSTEM_FLAG,Commands::ID>
{
    public:

        System();
        
        void systemSetup();

        void systemUpdate();

        void serviceSetup();



        SPIClass SDSPI;
        SPIClass SNSRSPI;

        CanBus<SYSTEM_FLAG> canbus;
         
        SiC43x Buck;

        ADS131M06 ADC;

        SensorHandler sensorHandler;
        EngineController ThanosR;

      
        SdFat_Store primarysd;

        uint32_t _OxAngle;
        uint32_t _FuelAngle;

    private:

        void initializeLoggers();
        void logReadings();
        void setupSPI();



        const std::string log_path = "/Logs";
        const std::string config_path = "/Config";
    

};