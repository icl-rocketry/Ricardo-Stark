/**
 * @file commands.cpp
 * @author Kiran de Silva (kd619@ic.ac.uk)
 * @brief Implementation of commands for system
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "commands.h"

#include <librnp/rnp_packet.h>
#include <libriccore/commands/commandhandler.h>
#include "Packets/rawADCPacket.h"

#include "EngineController/enginecontroller.h"
#include "EngineController/Ignition.h"
#include "EngineController/Shutdown.h"
#include "EngineController/Debug.h"


#include "system.h"

#include "esp_log.h"

void Commands::FreeRamCommand(System& sm, const RnpPacketSerialized& packet)
{	

	// ESP_LOGI("ch", "%s", "deserialize");

	SimpleCommandPacket commandpacket(packet);

	uint32_t freeram = esp_get_free_heap_size();
	//available in all states
	//returning as simple string packet for ease
	//currently only returning free ram
	if (commandpacket.arg == 0){
	MessagePacket_Base<0,static_cast<uint8_t>(decltype(System::commandhandler)::PACKET_TYPES::MESSAGE_RESPONSE)> message("FreeRam: " + std::to_string(esp_get_free_heap_size()));
	// this is not great as it assumes a single command handler with the same service ID
	// would be better if we could pass some context through the function parameters so it has an idea who has called it
	// or make it much clearer that only a single command handler should exist in the system
		message.header.source_service = sm.commandhandler.getServiceID(); 
		message.header.destination_service = packet.header.source_service;
		message.header.source = packet.header.destination;
		message.header.destination = packet.header.source;
		message.header.uid = packet.header.uid;
		sm.networkmanager.sendPacket(message);
	}
	else if (commandpacket.arg == 1)
	{
		BasicDataPacket<uint32_t,0,105> responsePacket(freeram);
		responsePacket.header.source_service = sm.commandhandler.getServiceID(); 
		responsePacket.header.destination_service = packet.header.source_service;
		responsePacket.header.source = packet.header.destination;
		responsePacket.header.destination = packet.header.source;
		responsePacket.header.uid = packet.header.uid;
		sm.networkmanager.sendPacket(responsePacket);	
	}

}


	void Commands::StarkTelemCommand(System& sm, const RnpPacketSerialized& packet)
{	
	SimpleCommandPacket commandpacket(packet);

	StarkTelemPacket starktelem;
	EngineController& engine();

	starktelem.header.type = static_cast<uint8_t>(10);
	starktelem.header.source = sm.networkmanager.getAddress();
	starktelem.header.source_service = sm.commandhandler.getServiceID();
	starktelem.header.destination = commandpacket.header.source;
	starktelem.header.destination_service = commandpacket.header.source_service;
	starktelem.header.uid = commandpacket.header.uid; 
	starktelem.servoVoltage = sm.Buck.getOutputV();
	// starktelem.pyroIMon = sm.Pyro.getIMon();
	starktelem.ch0sens = sm.PT0.getPressure();
	starktelem.ch1sens = sm.PT1.getPressure();
	starktelem.ch2sens = sm.ThanosR._OxInjPT.getPressure();
	starktelem.ch3sens = sm.ThanosR._ChamberPT.getPressure();
	starktelem.ch4sens = sm.PT4.getPressure();
	starktelem.ch5sens = sm.ThanosR._OxPT.getPressure();

	starktelem.Servo1Angle = sm.ThanosR.getOxAngle();
	starktelem.Servo2Angle = sm.ThanosR.getFuelAngle();
	
	starktelem.system_status = sm.systemstatus.getStatus();

	starktelem.system_time = millis();
	
	sm.networkmanager.sendPacket(starktelem);
	
}
	
 

void Commands::RawADCCommand(System& sm, const RnpPacketSerialized& packet)
{
	SimpleCommandPacket commandpacket(packet);

	RawADCPacket rawSensors;

	rawSensors.header.type = 10;
	rawSensors.header.source = sm.networkmanager.getAddress();
	rawSensors.header.source_service = sm.commandhandler.getServiceID();
	rawSensors.header.destination = commandpacket.header.source;
	rawSensors.header.destination_service = commandpacket.header.source_service;
	rawSensors.header.uid = commandpacket.header.uid;
	rawSensors.system_time = millis();

	rawSensors.ch0 = sm.ADC.getOutput(0);
	rawSensors.ch1 = sm.ADC.getOutput(1);
	rawSensors.ch2 = sm.ADC.getOutput(2); 
	rawSensors.ch3 = sm.ADC.getOutput(3);
	rawSensors.ch4 = sm.ADC.getOutput(4);
	rawSensors.ch5 = sm.ADC.getOutput(5);

	rawSensors.system_status = sm.systemstatus.getStatus();

	sm.networkmanager.sendPacket(rawSensors);
}	


void Commands::Idle(System& sm, const RnpPacketSerialized& packet)
{
	

}

void Commands::IgnitionCommand(System& sm, const RnpPacketSerialized& packet)
{


}

void Commands::ShutdownCommand(System& sm, const RnpPacketSerialized& packet)
{
	

}

void Commands::Debug(System& sm, const RnpPacketSerialized& packet)
{


}





