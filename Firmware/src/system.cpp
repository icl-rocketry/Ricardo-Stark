#include "system.h"

#include <memory>
#include <string>

#include <libriccore/riccoresystem.h>

#include <HardwareSerial.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include "Config/general_config.h"

#include "Commands/commands.h"
#include <librnp/default_packets/simplecommandpacket.h>

#include "States/idle.h"

#include "Storage/sdfat_store.h"
#include "Storage/sdfat_file.h"

#ifdef CONFIG_IDF_TARGET_ESP32S3
static constexpr int VSPI_BUS_NUM = 0;
static constexpr int HSPI_BUS_NUM = 1;
#else
static constexpr int VSPI_BUS_NUM = VSPI;
static constexpr int HSPI_BUS_NUM = HSPI;
#endif

System::System():
RicCoreSystem(Commands::command_map,Commands::defaultEnabledCommands,Serial),
SDSPI(VSPI_BUS_NUM),
SNSRSPI(HSPI_BUS_NUM),
Buck(systemstatus,int8_t , int8_t, 1, 1, PinMap::ServoVLog, 1500, 470),
canbus(systemstatus,PinMap::TxCan,PinMap::RxCan,3),
Servo1(PinMap::ServoPWM1, 0, networkmanager),
Servo2(PinMap::ServoPWM2, 1, networkmanager),
ADC0(SNSRSPI, PinMap::ADC0_Cs, PinMap::ADC_CLK),
primarysd(SDSPI,PinMap::SdCs_1,SD_SCK_MHZ(20),false,&systemstatus),
PT0(networkmanager, 2, ADC0, 3),
PT1(networkmanager, 3, ADC0, 2), //CHANGE THESE 
PT2(networkmanager, 4, ADC0, 1),
PT3(networkmanager, 5, ADC0, 0),
PT4(networkmanager, 4, ADC0, 1),
PT5(networkmanager, 5, ADC0, 0),
{};


void System::systemSetup(){
    
    Serial.setRxBufferSize(GeneralConfig::SerialRxSize);
    Serial.begin(GeneralConfig::SerialBaud);

    delay(2000);

    vspi.begin(PinMap::V_SCLK,PinMap::V_MISO,PinMap::V_MOSI);
    vspi.setFrequency(SD_SCK_MHZ(50));

    pinMode(PinMap::sdcs,OUTPUT);
    digitalWrite(PinMap::sdcs,HIGH);
   
    //intialize rnp message logger
    loggerhandler.retrieve_logger<RicCoreLoggingConfig::LOGGERS::SYS>().initialize(networkmanager);

    //initialize statemachine with idle state
    statemachine.initalize(std::make_unique<Idle>(systemstatus,commandhandler));
    //any other setup goes here
    // filestore.setup();
    // std::vector<directory_element_t> files;
    // bool error = filestore.ls(files);
    // RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(std::to_string(error));
    // for (auto e : files)
    // {
    //     RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(e.name);
    //     RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(std::to_string(e.size));
     
    // }

    // file_ptr = filestore.open("test.txt",(FILE_MODE)((uint8_t)FILE_MODE::WRITE | (uint8_t)FILE_MODE::CREATE | (uint8_t)FILE_MODE::AT_END));
    // file_ptr2 = filestore.open("test2.txt",(FILE_MODE)((uint8_t)FILE_MODE::WRITE | (uint8_t)FILE_MODE::CREATE | (uint8_t)FILE_MODE::AT_END));
    
    
};


void System::systemUpdate(){
    // uint32_t curr_time = micros();
    // if (curr_time - prevtime > 1000)
    // {
    //     std::string time_string = "\n" + std::to_string(curr_time) + "\n" + std::to_string(curr_time - prevtime) + "\n";
    //     if (file_ptr != nullptr)
    //     {
    //         try{
    //             file_ptr->appendCopy(data);
    //             file_ptr->appendCopy(std::vector<uint8_t>(time_string.begin(),time_string.end()));
    //             file_ptr2->appendCopy(data2);
    //             file_ptr2->appendCopy(std::vector<uint8_t>(time_string.begin(),time_string.end()));
    //         }
    //         catch (std::exception& e)
    //         {
    //             RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(e.what());
    //             throw e;
    //         }
    //     }
        // RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(std::to_string((uint8_t)filestore.getState()));
        // RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(std::to_string(esp_get_free_heap_size()));

    //     prevtime = curr_time;
        
    //  }


};