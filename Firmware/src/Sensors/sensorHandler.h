#pragma once
#include "Config/forward_decl.h"
#pragma once
#include "Sensors/ADS131M06.h"
#include "librrc/Remote/nrcremoteflowsensor.h"
#include "librrc/Remote/nrcremoteptap.h"
#include "config/pinmap_config.h"

// Handler for assigning specific sensors.


class SensorHandler
{
    public:
    SensorHandler(RnpNetworkManager& networkmanager, ADS131M06& ADC):
        _networkmanager(networkmanager),
        _ADC(ADC),    
        PT0(networkmanager,0),
        PT1(networkmanager,1),
        PT2(networkmanager,2),
        PT3(networkmanager,3),
        PT4(networkmanager,4),
        PT5(networkmanager,5),
        TF0(networkmanager,PCNT_UNIT_0,PCNT_CHANNEL_0,PinMap::Turbine,0.001146158078)
    {};

    void setup(){

            
        PT0.setup();
        PT1.setup();
        PT2.setup();
        PT3.setup();
        PT4.setup();
        PT5.setup();
        TF0.setup();

    };

    void serviceSetup(){


         uint8_t PT0Service = (uint8_t) Services::ID::PT0;
    _networkmanager.registerService(PT0Service,PT0.getThisNetworkCallback());

    uint8_t PT1Service = (uint8_t) Services::ID::PT1;
    _networkmanager.registerService(PT1Service,PT1.getThisNetworkCallback());

    uint8_t PT2Service = (uint8_t) Services::ID::PT2;
    _networkmanager.registerService(PT2Service,PT2.getThisNetworkCallback());

    uint8_t PT3Service = (uint8_t) Services::ID::PT3;
    _networkmanager.registerService(PT3Service,PT3.getThisNetworkCallback());

    uint8_t PT4Service = (uint8_t) Services::ID::PT4;
    _networkmanager.registerService(PT4Service,PT4.getThisNetworkCallback());

    uint8_t PT5Service = (uint8_t) Services::ID::PT5;
    _networkmanager.registerService(PT5Service,PT5.getThisNetworkCallback());



    }


    void update(){

    PT0.update(_ADC.getOutput(0));
    PT1.update(_ADC.getOutput(1));
    PT2.update(_ADC.getOutput(2));
    PT3.update(_ADC.getOutput(3));
    PT4.update(_ADC.getOutput(4));
    PT5.update(_ADC.getOutput(5));
    TF0.update();

    }


    float getPressure(uint8_t sensorID){

        switch(sensorID){
            case 0:
                return PT0.getPressure();
            case 1:
                return PT1.getPressure();
            case 2:
                return PT2.getPressure();
            case 3:
                return PT3.getPressure();
            case 4:
                return PT4.getPressure();
            case 5:
                return PT5.getPressure();

            default:
                return 0;
            
        }

    }

    float getFlow(){                    //ADD MORE TURBINE FLOWMETERS LATER IF WE EVER BUY ANY MORE LOL

        return TF0.getValue();
    }
    

     enum Sensor : uint8_t
        {
            ChamberPT = 0,
            OxInjPt = 1,
            WarmFuelInj = 2,
            ColdFuelInj = 3,
            Chn4 = 4,
            Chn5 = 5,
            Turbine = 6
        };

    private:

        RnpNetworkManager& _networkmanager;

        ADS131M06& _ADC;

        SPIClass SNSRSPI;

        NRCRemotePTap PT0;
        NRCRemotePTap PT1;
        NRCRemotePTap PT2;
        NRCRemotePTap PT3;
        NRCRemotePTap PT4;
        NRCRemotePTap PT5;
        NRCRemoteFlowSensor TF0;


};




