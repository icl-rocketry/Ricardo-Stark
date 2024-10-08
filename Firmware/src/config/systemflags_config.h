#pragma once

#include <stdint.h>
#include <type_traits>

enum class SYSTEM_FLAG:uint32_t{
    //state flags
    STATE_IDLE = (1 << 0),
    // STATE_IGNITION = (1 << 2),
    // STATE_CONTROLLED = (1 << 3),
    // STATE_SHUTDOWN = (1 << 4),

    //flags
    // STATE_DEBUG = (1 << 7),
    
    //critical messages 
    ERROR_SD_SPI = (1 << 10),
    ERROR_CAN = (1 << 11),
    ERROR_SNSR_SPI = (1 << 12),
    ERROR_SD = (1 << 13),
    ERROR_FUSE = (1 << 14),
    ERROR_BUCK = (1 << 15),
    ERROR_SERIAL = (1 << 16)
};

using system_flag_t = uint32_t;

