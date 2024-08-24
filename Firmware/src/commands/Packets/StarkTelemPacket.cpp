#include "StarkTelemPacket.h"

#include <librnp/rnp_packet.h>
#include <librnp/rnp_serializer.h>

#include <vector>



StarkTelemPacket::~StarkTelemPacket()
{};

StarkTelemPacket::StarkTelemPacket():
RnpPacket(0,
          10,
          size())
{};

StarkTelemPacket::StarkTelemPacket(const RnpPacketSerialized& packet):
RnpPacket(packet,size())
{
    getSerializer().deserialize(*this,packet.getBody());
};

void StarkTelemPacket::serialize(std::vector<uint8_t>& buf){
    RnpPacket::serialize(buf);
	size_t bufsize = buf.size();
	buf.resize(bufsize + size());
	std::memcpy(buf.data() + bufsize,getSerializer().serialize(*this).data(),size());
};