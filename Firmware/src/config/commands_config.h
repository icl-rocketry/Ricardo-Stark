#pragma once

#include <stdint.h>
#include <unordered_map>
#include <functional>
#include <initializer_list>

#include <libriccore/commands/commandhandler.h>
#include <librnp/rnp_packet.h>

#include "Config/forward_decl.h"
#include "Commands/commands.h"


namespace Commands
{
    enum class ID : uint8_t
    {
        NoCommand = 0,
        StarkTelem = 1,
        GetRawADC = 8,
        Idle = 50,
        Ignition = 69,
        Shutdown = 100,
        Debug = 150,      
        Free_Ram = 250

    };

    inline std::initializer_list<ID> defaultEnabledCommands = {ID::Free_Ram, ID::StarkTelem, ID::GetRawADC};

    inline std::unordered_map<ID, std::function<void(ForwardDecl_SystemClass &, const RnpPacketSerialized &)>> command_map{
        {ID::Free_Ram, FreeRamCommand},
        {ID::StarkTelem, StarkTelemCommand},
        {ID::GetRawADC, RawADCCommand},
        {ID::Idle, Idle},
        {ID::Ignition, IgnitionCommand},
        {ID::Shutdown, ShutdownCommand},
        {ID::Debug, Debug}

        };



};