#pragma once

#include <librnp/rnp_serializer.h>
#include <unistd.h>

class TelemetryLogframe{
private:  
    static constexpr auto getSerializer()
    {
        auto ret = RnpSerializer(
            &TelemetryLogframe::ch0sens,
            &TelemetryLogframe::ch1sens,
            &TelemetryLogframe::ch2sens,
            &TelemetryLogframe::ch3sens,
            &TelemetryLogframe::ch4sens,
            &TelemetryLogframe::ch5sens,
            &TelemetryLogframe::timestamp         

        );
        return ret;
    }

public:
    //Sensors
     float ch0sens,ch1sens,ch2sens,ch3sens,ch4sens,ch5sens;
    
    
    int16_t rssi; 
    float snr;

    
    uint64_t timestamp;

    std::string stringify()const{
        return getSerializer().stringify(*this) + "\n";
    };

};
