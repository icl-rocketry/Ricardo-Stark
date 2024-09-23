#pragma once

#include "stdint.h"
#include "config/pinmap_config.h"
#include "libriccore/platform/esp32/adc.h"

class Imon

{   

    public:

        Imon():adc(PinMap::PyroIMon){};
        
        void setup()
        {   
            adc.setup();    
        };
        
        void update(){

            adc.update();

            int16_t raw_adc = adc.getADC();
            // Serial.println (raw_adc);
            m_current = (m_voltage*1e-6)/(RImon*GImon);

        };

    private:

        ADC adc;
        float m_current;
        float m_voltage = 3.3;
        uint8_t GImon = 1;
        uint16_t RImon = 681;
        float getCurrent(){ return m_current;};


};