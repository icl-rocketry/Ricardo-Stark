#pragma once

#include <librnp/rnp_packet.h>
#include <librnp/rnp_serializer.h>

#include <vector>

//shamelessly copied from chad's telemetry packet

class StarkTelemPacket : public RnpPacket{
    private:
    //serializer framework
        static constexpr auto getSerializer()
        {
            auto ret = RnpSerializer(
                &StarkTelemPacket::servoVoltage,
                // &StarkTelemPacket::pyroIMon,
                &StarkTelemPacket::ch0sens,
                &StarkTelemPacket::ch1sens,
                &StarkTelemPacket::ch2sens,
                &StarkTelemPacket::ch3sens,
                &StarkTelemPacket::ch4sens,
                &StarkTelemPacket::ch5sens,
                &StarkTelemPacket::Servo1Angle,
                &StarkTelemPacket::Servo2Angle,
                &StarkTelemPacket::system_status,
                &StarkTelemPacket::system_time
            );

            return ret;
        }
        
    public:
        ~StarkTelemPacket();

        StarkTelemPacket();
        /**
         * @brief Deserialize Telemetry Packet
         * 
         * @param data 
         */
        StarkTelemPacket(const RnpPacketSerialized& packet);

        /**
         * @brief Serialize Telemetry Packet
         * 
         * @param buf 
         */
        void serialize(std::vector<uint8_t>& buf) override;

        float servoVoltage;
        // float pyroIMon;
        float ch0sens;
        float ch1sens;
        float ch2sens;
        float ch3sens;
        float ch4sens;
        float ch5sens;

        uint32_t Servo1Angle;
        uint32_t Servo2Angle;

        uint32_t system_status;
        uint64_t system_time;

        static constexpr size_t size(){
            return getSerializer().member_size();
        }

};


