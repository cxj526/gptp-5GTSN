#ifndef SRC_CXJ_GPTP_H_
#define SRC_CXJ_GPTP_H_

#include "inet/common/INETDefs.h"
//#include "inet/common/ModuleRefByPar.h"
#include "omnetpp.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "gPtpPacket_m.h"
#include "string.h"
#include "inet/linklayer/common/MacAddress.h"
#include "Clock.h"
//class inet::Packet Packet;
//class inet::IInterfaceTable IInterfaceTable;
using namespace omnetpp;
using namespace inet;
namespace cxj{
class gPtp : public omnetpp::cListener, public cSimpleModule
{
    //parameters:
        //inet::IInterfaceTable interfaceTable;

        GptpNodeType gptpNodeType;
        int slavePortId = -1; // interface ID of slave port
        //int masterPortIds = -1; // interface IDs of master ports
        int masterPortIds = -1;
        simtime_t correctionField;

        double gmRateRatio = 1.0;
        double receivedRateRatio = 1.0;

        simtime_t originTimestamp; // last outgoing timestamp

        simtime_t receivedTimeSync;

        simtime_t syncInterval;
        simtime_t pdelayInterval;

        uint16_t sequenceId = 0;
        /* Slave port - Variables is used for Peer Delay Measurement */
        uint16_t lastSentPdelayReqSequenceId = 0;
        simtime_t peerDelay;
        simtime_t peerRequestReceiptTimestamp;  // pdelayReqIngressTimestamp from peer (received in GptpPdelayResp)
        simtime_t peerResponseOriginTimestamp; // pdelayRespEgressTimestamp from peer (received in GptpPdelayRespFollowUp)
        simtime_t pdelayRespEventIngressTimestamp;  // receiving time of last GptpPdelayResp
        simtime_t pdelayReqEventEgressTimestamp;   // sending time of last GptpPdelayReq
        simtime_t pDelayReqProcessingTime;  // processing time between arrived PDelayReq and send of PDelayResp
        bool rcvdPdelayResp = false;

        simtime_t sentTimeSyncSync;

        /* Slave port - Variables is used for Rate Ratio. All times are drifted based on constant drift */
        // clocktime_t sentTimeSync;
        simtime_t newLocalTimeAtTimeSync;
        simtime_t oldLocalTimeAtTimeSync;
        simtime_t peerSentTimeSync;  // sending time of last received GptpSync
        simtime_t syncIngressTimestamp;  // receiving time of last incoming GptpSync

        bool rcvdGptpSync = false;
        uint16_t lastReceivedGptpSyncSequenceId = 0xffff;

        // self timers:
        //ClockEvent* selfMsgSync = nullptr;
        //ClockEvent* selfMsgDelayReq = nullptr;
        //ClockEvent* requestMsg = nullptr;
        cMessage* selfMsgSync = nullptr;
        cMessage* selfMsgDelayReq = nullptr;
        cMessage* requestMsg = nullptr;

        //clock module pointer
       // Clock* clock;
        // Statistics information: // TODO remove, and replace with emit() calls
        static simsignal_t localTimeSignal;
        static simsignal_t timeDifferenceSignal;
        static simsignal_t rateRatioSignal;
        static simsignal_t peerDelaySignal;
      public:
        static const inet::MacAddress GPTP_MULTICAST_ADDRESS;

      protected:

        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;
        //virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
        virtual void handleSelfMessage(cMessage *msg);

      public:
        virtual ~gPtp();
        void sendPacketToNIC(inet::Packet *packet, int portId);

        void sendSync();
        void sendFollowUp(int portId, const GptpSync *sync, simtime_t preciseOriginTimestamp);
        void sendPdelayReq();
        //void sendPdelayResp(GptpReqAnswerEvent *req);
        void sendPdelayRespFollowUp(int portId, const GptpPdelayResp* resp);

        void processSync(inet::Packet *packet, const GptpSync* gptp);
        void processFollowUp(inet::Packet *packet, const GptpFollowUp* gptp);
        void processPdelayReq(inet::Packet *packet, const GptpPdelayReq* gptp);
        void processPdelayResp(inet::Packet *packet, const GptpPdelayResp* gptp);
        void processPdelayRespFollowUp(inet::Packet *packet, const GptpPdelayRespFollowUp* gptp);

        simtime_t getCalculatedDrift(Clock *clock, simtime_t value) { return omnetpp::SimTime::ZERO; }   //yong 0应该没啥问题
        void synchronize();

        virtual void receiveSignal(cComponent *source, simsignal_t signal, cObject *obj, cObject *details) override;//重写于cListener


};

}
#endif /* SRC_INET48021AS_GPTP_H_ */
