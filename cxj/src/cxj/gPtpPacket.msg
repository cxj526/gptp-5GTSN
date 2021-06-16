//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 


cplusplus {{

#include "omnetpp/simtime.h"
#include "omnetpp.h"
#include "inet/common/Units.h"
#include "inet/common/INETUtils.h"
#include "inet/common/INETDefs.h"
#include "inet/common/INETDefs_m.h"
#include "inet/common/packet/chunk/Chunk_m.h"
#include "inet/common/TagBase_m.h"
namespace cxj {
using namespace inet::units::values;
const B GPTP_SYNC_1STEP_PACKET_SIZE = B(76);
const B GPTP_SYNC_2STEP_PACKET_SIZE = B(44);
const B GPTP_FOLLOW_UP_PACKET_SIZE = B(76);
const B GPTP_PDELAY_REQ_PACKET_SIZE = B(54);
const B GPTP_PDELAY_RESP_PACKET_SIZE = B(54);
const B GPTP_PDELAY_RESP_FOLLOW_UP_PACKET_SIZE = B(54);
}
}}

class noncobject omnetpp::simtime_t;
class noncobject omnetpp::SimTime;
class noncobject inet::FieldsChunk;
class noncobject inet::units::values;
class noncobject inet::TagBase;
namespace cxj;

//
// TODO generated message class
//

enum GptpNodeType
{
    MASTER_NODE = 11;
    BRIDGE_NODE = 12;
    SLAVE_NODE  = 13;
}

enum GptpPortType
{
    MASTER_PORT  = 2;
    SLAVE_PORT   = 1;
    PASSIVE_PORT = 0;
}

enum GptpMessageType
{
    GPTPTYPE_SYNC    = 1010;
    GPTPTYPE_FOLLOW_UP = 1011;
    GPTPTYPE_PDELAY_REQ = 1014;
    GPTPTYPE_PDELAY_RESP = 1012;
    GPTPTYPE_PDELAY_RESP_FOLLOW_UP = 1013;
}

enum GptpSelfMsgKind {
    GPTP_SELF_REQ_ANSWER_KIND = 101;
    GPTP_SELF_MSG_SYNC = 103;
    GPTP_REQUEST_TO_SEND_SYNC = 104;
    GPTP_SELF_MSG_PDELAY_REQ = 105;
}

struct PortIdentity
{
    uint64_t clockIdentity;
    uint16_t portNumber;
};

// ieee802.1AS-2020 11.4.2
class GptpBase extends inet::FieldsChunk
{
    int messageType @enum(GptpMessageType);
   // uint16_t messageLength; // currently unused
    //uint8_t domainNumber; // currently unused
   // uint16_t flags; // currently unused
    omnetpp::simtime_t correctionField;
    PortIdentity sourcePortIdentity;
   // uint16_t sequenceId; // currently unused
   // uint8_t logMessageInterval; // currently unused
}

class GptpSync extends GptpBase
{
    messageType = GPTPTYPE_SYNC;
    //flags = twoStepFlag;
    chunkLength = GPTP_SYNC_2STEP_PACKET_SIZE;
    omnetpp::simtime_t originTimestamp; // filled when twoStep flag is FALSE
    //omnetpp::simtime_t aaa;
    // followUpInformationTLV; // filled when twoStep flag is FALSE
}

class GptpFollowUp extends GptpBase
{
    messageType = GPTPTYPE_FOLLOW_UP;
    chunkLength = GPTP_FOLLOW_UP_PACKET_SIZE;
    omnetpp::simtime_t preciseOriginTimestamp;  // 11.4.4.2.1
    // followUpInformationTLV:
    double rateRatio;  // 11.4.4.3.6 cumulativeScaledRateOffset, relative to GrandMaster
    // uint16_t gmTimeBaseIndicator;
    // ScaledNs lastGmPhaseChange;
    // int32_t scaledLastGmFreqChange;
    // ??? int numberOfHops;
}

class GptpPdelayReq extends GptpBase
{
    messageType = GPTPTYPE_PDELAY_REQ;
    chunkLength = GPTP_PDELAY_REQ_PACKET_SIZE;
    omnetpp::simtime_t reserved1;
    omnetpp::simtime_t reserved2;
}

class GptpPdelayResp extends GptpBase
{
    messageType = GPTPTYPE_PDELAY_RESP;
    chunkLength = GPTP_PDELAY_RESP_PACKET_SIZE;
    omnetpp::simtime_t requestReceiptTimestamp;
    PortIdentity requestingPortIdentity;
}

class GptpPdelayRespFollowUp extends GptpBase
{
    messageType = GPTPTYPE_PDELAY_RESP_FOLLOW_UP;
    chunkLength = GPTP_PDELAY_RESP_FOLLOW_UP_PACKET_SIZE;
    omnetpp::simtime_t responseOriginTimestamp;
    PortIdentity requestingPortIdentity;
}

class GptpIngressTimeInd extends inet::TagBase
{
    omnetpp::simtime_t arrivalClockTime;
}

