/**
 * @file services_config.h
 * @author Kiran de Silva (kd619@ic.ac.uk)
 * @brief Defintion of user defined services
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <stdint.h>


namespace Services{
    /**
     * @brief ID of user defined services NB start at 2, all ID's below 2 are reserved for default services found in 'rnp_networkmanager.h'
     * 
     */
    enum class ID:uint8_t{

        Engine = 10,
        Servo1 = 11,
        Servo2 = 12,
        LED = 15,
        Pyro = 20,
        PT0 = 30,
        PT1 = 31,
        PT2 = 32,
        PT3 = 33,
        PT4 = 34,
        PT5 = 35,
        Engine = 69

    };

};