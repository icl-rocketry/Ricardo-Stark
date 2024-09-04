#pragma once

#include <libriccore/riccoresystem.h>

#include <memory>
#include <librrc/Remote/nrcremoteservo.h>
#include <librrc/Remote/nrcremoteptap.h> 
#include <librrc/Remote/nrcremotepyro.h>

#include "Sensors/ADS131M06.h"
#include "SiC43x.h"


#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include <libriccore/networkinterfaces/can/canbus.h>
#include "config/pinmap_config.h"

#include "states/Engine.h"


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


        // EngineController ThanosR;

        SPIClass SDSPI;
        SPIClass SNSRSPI;

        CanBus<SYSTEM_FLAG> canbus;
         
        SiC43x Buck;

        ADS131M06 ADC0;

      
        SdFat_Store primarysd;

    private:

        void initializeLoggers();
        void logReadings();

        const std::string log_path = "/Logs";
        const std::string config_path = "/Config";
        uint32_t telemetry_log_delta = 5000;
        uint32_t prev_telemetry_log_time;
        uint32_t prevtime;

        

        


};