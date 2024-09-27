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

#include "EngineController/enginecontroller.h"
#include "EngineController/Ignition.h"
#include "EngineController/Controlled.h"

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


        EngineController ThanosR;

        SPIClass SDSPI;
        SPIClass SNSRSPI;

        CanBus<SYSTEM_FLAG> canbus;
         
        SiC43x Buck;

        ADS131M06 ADC;

        NRCRemotePTap PT0;
        NRCRemotePTap PT1;
        NRCRemotePTap PT2;
        NRCRemotePTap PT3;
        NRCRemotePTap PT4;
        NRCRemotePTap PT5;

      
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