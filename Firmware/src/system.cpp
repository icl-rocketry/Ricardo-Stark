#include "system.h"

#include <memory>
#include <string>

#include <libriccore/riccoresystem.h>

#include <HardwareSerial.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include "Config/general_config.h"
#include "Config/services_config.h"

#include "Loggers/TelemetryLogger/telemetrylogframe.h"

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
I2C(0),
canbus(systemstatus,PinMap::TxCan,PinMap::RxCan,3),
Buck(systemstatus, PinMap::ServoVLog, 1500, 470),
ADC(SNSRSPI, PinMap::ADS_Cs, PinMap::ADS_Clk,2),
pyroPinExpander0(0x20,I2C),
pyroPowerSwitch(pyroPinExpander0,PinMap::PyroPowerSwitch),
sensorHandler(networkmanager, ADC),
ThanosR(networkmanager, sensorHandler,pyroPinExpander0),   
primarysd(SDSPI,PinMap::SdCs,SD_SCK_MHZ(20),false, &systemstatus)
{};


void System::systemSetup(){
    
    Serial.setRxBufferSize(GeneralConfig::SerialRxSize);
    Serial.begin(GeneralConfig::SerialBaud);

    // Serial.println("Test");

    SDSPI.begin(PinMap::V_SCLK,PinMap::V_MISO,PinMap::V_MOSI);
    SDSPI.setFrequency(SD_SCK_MHZ(20));

    pinMode(PinMap::SdCs,OUTPUT);
    digitalWrite(PinMap::SdCs,HIGH);

    //initialize statemachine with idle state
    statemachine.initalize(std::make_unique<Idle>(systemstatus,commandhandler));
    //any other setup goes here


    pinMode(PinMap::SdCs, OUTPUT);
    // pinMode(PinMap::SdEN, OUTPUT);
    pinMode(PinMap::ADS_Cs, OUTPUT);

    digitalWrite(PinMap::SdCs, HIGH);
    // digitalWrite(PinMap::SdEN, LOW);
    digitalWrite(PinMap::ADS_Cs, HIGH);


    // pinMode(PinMap::LED, OUTPUT);
    // digitalWrite(PinMap::LED, HIGH); 

    canbus.setup();
    Buck.setup();
    setupSPI();
    ADC.setup();
    setupI2C();

    setupPyroPinExpander();



    sensorHandler.setup();

 
    networkmanager.setNodeType(NODETYPE::HUB);
    networkmanager.setNoRouteAction(NOROUTE_ACTION::BROADCAST,{1,3});
    networkmanager.addInterface(&canbus);

    uint8_t Engineservice = (uint8_t) Services::ID::Engine;
    networkmanager.registerService(Engineservice,ThanosR.getThisNetworkCallback());



    primarysd.setup();  
    initializeLoggers();

    

    ThanosR.setup();

    //enable pyro power
    pyroPowerSwitch.digitalWrite(1);
    RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>("Pyro power enabled");
    
};

void System::setupSPI(){
    SDSPI.begin(PinMap::V_SCLK,PinMap::V_MISO,PinMap::V_MOSI, PinMap::SdCs);
    SDSPI.setFrequency(2000000);
    SDSPI.setBitOrder(MSBFIRST);
    SDSPI.setDataMode(SPI_MODE0);

    SNSRSPI.begin(PinMap::H_SCLK, PinMap::H_MISO, PinMap::H_MOSI, PinMap::ADS_Cs);
    SNSRSPI.setFrequency(5000000);
    SNSRSPI.setBitOrder(MSBFIRST);
    SNSRSPI.setDataMode(SPI_MODE1);
}

 

void System::systemUpdate(){
    
    Buck.update();
    ADC.update();
    ThanosR.update(); 

    sensorHandler.update();

    _OxAngle = ThanosR.getOxAngle();
    _FuelAngle = ThanosR.getFuelAngle();

    logReadings();

};

    void System::logReadings(){

    TelemetryLogframe logframe;

    uint32_t system_status;
    uint64_t system_time;

    
    logframe.ch0sens = sensorHandler.getPressure(0);
    logframe.ch1sens = sensorHandler.getPressure(1);
    logframe.ch2sens = sensorHandler.getPressure(2);
    logframe.ch3sens = sensorHandler.getPressure(3);
    logframe.ch4sens = sensorHandler.getPressure(4);
    logframe.ch5sens = sensorHandler.getPressure(5);
    logframe.oxangle = _OxAngle;
    logframe.fuelangle = _FuelAngle;
    logframe.timestamp = esp_timer_get_time();

    RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::TELEMETRY>(logframe);

}

void System::setupI2C()
{
    I2C.begin(PinMap::_SDA, PinMap::_SCL, GeneralConfig::I2C_FREQUENCY);
}

void System::setupPyroPinExpander()
{
    if (pyroPinExpander0.setup())
    {
        RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>("I2C pyro pin expander alive");

        pyroPowerSwitch.digitalWrite(0); // ensure off
        pyroPowerSwitch.pinMode(PCA9534Gpio::PINMODE::GPIO_OUTPUT);
        

    }
    else
    {
        RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>("I2C pyro pin expander failed to respond");
    }

};

void System::initializeLoggers()
{
    // check if sd card is mounted
    if (primarysd.getState() != StoreBase::STATE::NOMINAL)
    {
        loggerhandler.retrieve_logger<RicCoreLoggingConfig::LOGGERS::SYS>().initialize(nullptr, networkmanager);

        return;
    }

    // open log files
    // get unique directory for logs
    std::string log_directory_path = primarysd.generateUniquePath(log_path, "");
    // make new directory
    primarysd.mkdir(log_directory_path);

    std::unique_ptr<WrappedFile> syslogfile = primarysd.open(log_directory_path + "/syslog.txt", static_cast<FILE_MODE>(O_WRITE | O_CREAT | O_AT_END));
    std::unique_ptr<WrappedFile> telemetrylogfile = primarysd.open(log_directory_path + "/telemetrylog.txt", static_cast<FILE_MODE>(O_WRITE | O_CREAT | O_AT_END),50);

    // intialize sys logger
    loggerhandler.retrieve_logger<RicCoreLoggingConfig::LOGGERS::SYS>().initialize(std::move(syslogfile), networkmanager);

    // initialize telemetry logger
    loggerhandler.retrieve_logger<RicCoreLoggingConfig::LOGGERS::TELEMETRY>().initialize(std::move(telemetrylogfile),[](std::string_view msg){RicCoreLogging::log<RicCoreLoggingConfig::LOGGERS::SYS>(msg);});
}




