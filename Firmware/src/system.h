#pragma once

#include <libriccore/riccoresystem.h>

#include <memory>
#include <librrc/Remote/nrcremoteservo.h>
#include <librrc/Remote/nrcremoteptap> 
#include <librrc/Remote/nrcremotepyro.h>
#include "Sensors/ADS131M06.h"


#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"

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

         SiC43x Buck;

         CanBus<SYSTEM_FLAG> canbus;

    private:

        SPIClass SDSPI;
        SPIClass SNSRSPI;

        NRCRemoteServo Servo1;
        NRCRemoteServo Servo2;

        NRCRemotePyro Pyro;

        ADS131M06 ADC0;

        NRCRemotePTap PT0;
        NRCRemotePTap PT1;
        NRCRemotePTap PT2;
        NRCRemotePTap PT3;
        NRCRemotePTap PT4;
        NRCRemotePTap PT5;


        SdFat_Store primarysd;

        std::unique_ptr<WrappedFile> file_ptr;
        std::unique_ptr<WrappedFile> file_ptr2;

        uint32_t prevtime;

        std::vector<uint8_t> data;
        std::vector<uint8_t> data2;

        

        


};