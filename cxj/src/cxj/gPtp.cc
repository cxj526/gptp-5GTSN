#include "gPtp.h"
#include "gPtpPacket_m.h"
#include <omnetpp.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include <utility>
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/linklayer/ethernet/Ethernet.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/linklayer/ethernet/EtherPhyFrame_m.h"
#include "inet/common/Simsignals.h"

#include "inet/common/packet/chunk/Chunk_m.h"
#include "inet/linklayer/base/MacProtocolBase.h"
#include "inet/common/Protocol.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/IProtocolRegistrationListener.h"
using namespace omnetpp;
using namespace inet;
namespace cxj{
Define_Module(gPtp);

simsignal_t gPtp::localTimeSignal = cComponent::registerSignal("localTime");
simsignal_t gPtp::timeDifferenceSignal = cComponent::registerSignal("timeDifference");
simsignal_t gPtp::rateRatioSignal = cComponent::registerSignal("rateRatio");
simsignal_t gPtp::peerDelaySignal = cComponent::registerSignal("peerDelay");

// MAC address:
//   01-80-C2-00-00-02 for TimeSync (ieee 802.1as-2020, 13.3.1.2)
//   01-80-C2-00-00-0E for Announce and Signaling messages, for Sync, Follow_Up, Pdelay_Req, Pdelay_Resp, and Pdelay_Resp_Follow_Up messages
const MacAddress gPtp::GPTP_MULTICAST_ADDRESS("01:80:C2:00:00:0E");

// EtherType:
//   0x8809 for TimeSync (ieee 802.1as-2020, 13.3.1.2)
//   0x88F7 for Announce and Signaling messages, for Sync, Follow_Up, Pdelay_Req, Pdelay_Resp, and Pdelay_Resp_Follow_Up messages

gPtp::~gPtp()
{
    //cancelAndDeleteClockEvent(selfMsgDelayReq);
    //cancelAndDeleteClockEvent(selfMsgSync);
    //cancelAndDeleteClockEvent(requestMsg);
    cancelAndDelete(selfMsgSync);
    cancelAndDelete(selfMsgDelayReq);
    cancelAndDelete(requestMsg);
}

void gPtp::initialize(int stage)
{
    //ClockUserModuleBase::initialize(stage);
    //cModule* parentModule = getParentModule()->getParentModule();

    //if(parentModule->getSubmodule("clock") != nullptr){
    //    clock =  check_and_cast<Clock*>(parentModule->getSubmodule("clock"));
    //}

    if (stage == inet::INITSTAGE_LOCAL) {
        gptpNodeType = static_cast<GptpNodeType>(cEnum::get("GptpNodeType", "cxj")->resolve(par("gptpNodeType")));
        syncInterval = par("syncInterval");
        pDelayReqProcessingTime = par("pDelayReqProcessingTime");
    }
    if (stage == inet::INITSTAGE_LINK_LAYER) {
        peerDelay = 0;
        receivedTimeSync = SimTime::ZERO;

        //interfaceTable.reference(this, "interfaceTableModule", true);
        IInterfaceTable *ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);


        const char *str = par("slavePort");
        if (*str) {
            if (gptpNodeType == MASTER_NODE)
                throw cRuntimeError("Parameter inconsistency: MASTER_NODE with slave port");
            //auto nic = CHK(interfaceTable->findInterfaceByName(str));
           // slavePortId = nic->getInterfaceId();
            //nic->subscribe(transmissionEndedSignal, this);
            //nic->subscribe(receptionEndedSignal, this);
            InterfaceEntry *ie = ift->findInterfaceByName(str);
            slavePortId = ie->getInterfaceId();
            ie->subscribe(inet::packetSentSignal, this);
            ie->subscribe(inet::packetReceivedSignal, this);
        }
        else
            if (gptpNodeType != MASTER_NODE)
                throw cRuntimeError("Parameter error: Missing slave port for %s", par("gptpNodeType").stringValue());

        //auto v = check_and_cast<cValueArray *>(par("masterPorts").objectValue())->asStringVector();
        const char* v = par("masterPorts");
         //std::string v[] = par("masterPorts");
       /* int count = 0;
        while(*v){
            if(*v == ','){
                count++;
            }
            v++;
        }
        char *v_cp = new char(count);
        std::strcpy(v_cp, v);
        const char *delim = ",";
        char *subv = strtok(v_cp , delim);
       // int num =
        char** sss = new char*[4];
        int i = 0;
        while(subv != nullptr){
            sss[i] = new char[5];
            //std::printf(" %s\n",subv);
            //sss[i++] = subv;
            strcpy(sss[i], subv);
            i++;
            subv = strtok(nullptr,delim);
            delete[] sss[i];
        }*/

        if (*v and gptpNodeType != SLAVE_NODE)
            throw cRuntimeError("Parameter error: Missing any master port for %s", par("gptpNodeType").stringValue());
        //int j = 0;
        //for ( j = 0 ; j < 4;j++) {
            //auto nic = CHK(interfaceTable->findInterfaceByName(p.c_str()));
           // int portId = nic->getInterfaceId();
            InterfaceEntry *nic = ift->findInterfaceByName("eth0");

            int portId = nic->getInterfaceId();
            if (portId == slavePortId)
                throw cRuntimeError("Parameter error: the port '%s' specified both master and slave port", v);
            //masterPortIds.insert(portId);
            masterPortIds = portId;
            nic->subscribe(inet::packetSentSignal, this);
            nic->subscribe(inet::packetReceivedSignal, this);
        //}

        if (slavePortId != -1) {
            //interfaceTable->getInterfaceById(slavePortId)->addMulticastMacAddress(GPTP_MULTICAST_ADDRESS);
            ift->getInterfaceById(slavePortId)->setMacAddress(GPTP_MULTICAST_ADDRESS);
        }
        /*for (auto id: masterPortIds) {
            //interfaceTable->getInterfaceById(id)->addMulticastMacAddress(GPTP_MULTICAST_ADDRESS);
            ift->getInterfaceById(id)->setMacAddress(GPTP_MULTICAST_ADDRESS);
        }*/
        if (masterPortIds != -1) {
            ift->getInterfaceById(masterPortIds)->setMacAddress(GPTP_MULTICAST_ADDRESS);
            //interfaceTable->getInterfaceById(slavePortId)->addMulticastMacAddress(GPTP_MULTICAST_ADDRESS);
        }

        correctionField = par("correctionField");

        gmRateRatio = 1.0;

        registerProtocol(Protocol::ipv4, gate("socketOut"), gate("socketIn")); //注意下，协议注册

        /* Only grandmaster in the domain can initialize the synchronization message periodically
         * so below condition checks whether it is grandmaster and then schedule first sync message */
        if(gptpNodeType == MASTER_NODE)
        {
            // Schedule Sync message to be sent
            selfMsgSync = new cMessage("selfMsgSync",GPTP_SELF_MSG_SYNC);
            //selfMsgSync = new ClockEvent("selfMsgSync", GPTP_SELF_MSG_SYNC);

            simtime_t scheduleSync = par("syncInitialOffset");
           // originTimestamp = clock->getCurrentTime() + scheduleSync;//注意这里我们的clock是自己定义的，所以可能会改
            scheduleAt(scheduleSync, selfMsgSync);
        }
        if(slavePortId != -1)
        {
            requestMsg = new cMessage("requestToSendSync", GPTP_REQUEST_TO_SEND_SYNC);

            // Schedule Pdelay_Req message is sent by slave port
            // without depending on node type which is grandmaster or bridge
            selfMsgDelayReq = new cMessage("selfMsgPdelay", GPTP_SELF_MSG_PDELAY_REQ);
            pdelayInterval = par("pdelayInterval");
            scheduleAt(par("pdelayInitialOffset"), selfMsgDelayReq);

        }
        WATCH(peerDelay);
    }
}

void gPtp::handleSelfMessage(cMessage *msg)
{
    switch(msg->getKind()) {
        case GPTP_SELF_MSG_SYNC:
            // masterport:
            ASSERT(selfMsgSync == msg);
            sendSync();

            /* Schedule next Sync message at next sync interval
             * Grand master always works at simulation time */
            scheduleAt(syncInterval, selfMsgSync);

            break;

        case GPTP_SELF_REQ_ANSWER_KIND:
            // masterport: ccc
            //sendPdelayResp(check_and_cast<GptpReqAnswerEvent*>(msg));
            delete msg;
            break;

        case GPTP_SELF_MSG_PDELAY_REQ:
        // slaveport:
            sendPdelayReq(); // on slaveports only
            scheduleAt(pdelayInterval, selfMsgDelayReq);
            break;

        default:
            throw cRuntimeError("Unknown self message (%s)%s, kind=%d", msg->getClassName(), msg->getName(), msg->getKind());
    }
}

void gPtp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        handleSelfMessage(msg);
    }
    else {
        Packet *packet = check_and_cast<Packet *>(msg);
        auto gptp = packet->peekAtFront<GptpBase>();
        auto gptpMessageType = gptp->getMessageType();
        auto incomingNicId = packet->getTag<InterfaceInd>()->getInterfaceId();

        if (incomingNicId == slavePortId) {
            // slave port
            switch (gptpMessageType) {
                case GPTPTYPE_SYNC:
                    processSync(packet, check_and_cast<const GptpSync *>(gptp.get()));
                    break;
                case GPTPTYPE_FOLLOW_UP:
                    processFollowUp(packet, check_and_cast<const GptpFollowUp *>(gptp.get()));
                    // Send a request to send Sync message
                    // through other gptp Ethernet interfaces
                    if(gptpNodeType == BRIDGE_NODE)
                        sendSync();
                    break;
                case GPTPTYPE_PDELAY_RESP:
                    processPdelayResp(packet, check_and_cast<const GptpPdelayResp *>(gptp.get()));
                    break;
                case GPTPTYPE_PDELAY_RESP_FOLLOW_UP:
                    processPdelayRespFollowUp(packet, check_and_cast<const GptpPdelayRespFollowUp *>(gptp.get()));
                    break;
                default:
                    throw cRuntimeError("Unknown gPTP packet type: %d", (int)(gptpMessageType));
            }
        }
        else if(masterPortIds != -1){
        //else if (masterPortIds.find(incomingNicId) != masterPortIds.end()) { // ccc
            // master port
            if(gptpMessageType == GPTPTYPE_PDELAY_REQ) {
                processPdelayReq(packet, check_and_cast<const GptpPdelayReq *>(gptp.get()));
            }
            else {
                throw cRuntimeError("Unaccepted gPTP type: %d", (int)(gptpMessageType));
            }
        }
        else {
            // passive port ccc
            EV_ERROR << "Message " << msg->getName() << " arrived on passive port " << incomingNicId << ", dropped\n";
        }
        delete msg;
    }
}

void gPtp::sendPacketToNIC(Packet *packet, int portId)
{
    //auto networkInterface = interfaceTable->getInterfaceById(portId);
   // auto protocolTag = packet->findTag<PacketProtocolTag>();
    //if (protocolTag) {
    //const Protocol *protocol = protocolTag->getProtocol();
    auto protocolTag = packet->findTag<PacketProtocolTag>();

    //auto networkInterface = packet->
    //ccc
    EV_INFO << "Sending " << packet << " to output interface = " << protocolTag->getFullName() << ".\n";
    packet->addTag<InterfaceReq>()->setInterfaceId(portId);
    packet->addTag<PacketProtocolTag>()->setProtocol(&Protocol::ipv4);
    packet->addTag<DispatchProtocolInd>()->setProtocol(&Protocol::ipv4);
    auto protocol = protocolTag->getProtocol();
    if (protocol != nullptr)
        packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(protocol);
    else
        packet->removeTagIfPresent<DispatchProtocolReq>();
    send(packet, "socketOut");
}

void gPtp::sendSync()
{
    auto packet = new Packet("GptpSync");
    packet->addTag<MacAddressReq>()->setDestAddress(GPTP_MULTICAST_ADDRESS);
    auto gptp = makeShared<GptpSync>();
    /* OriginTimestamp always get Sync departure time from grand master */
    if (gptpNodeType == MASTER_NODE) {
       // originTimestamp = clock->getCurrentTime();
    }
    gptp->setOriginTimestamp(SimTime::ZERO);
    //gptp->setSequenceId(sequenceId++);

    //sentTimeSyncSync = clock->getCurrentTime();
    packet->insertAtFront(gptp);

   // for (auto port: masterPortIds)
        sendPacketToNIC(packet->dup(), masterPortIds);
    delete packet;

    // The sendFollowUp(portId) called by receiveSignal(), when GptpSync sent
}

void gPtp::sendFollowUp(int portId, const GptpSync *sync, simtime_t preciseOriginTimestamp)
{
    auto packet = new Packet("GptpFollowUp");
    packet->addTag<MacAddressReq>()->setDestAddress(GPTP_MULTICAST_ADDRESS);
    auto gptp = makeShared<GptpFollowUp>();
    gptp->setPreciseOriginTimestamp(preciseOriginTimestamp);
    //gptp->setSequenceId(sync->getSequenceId());

    if (gptpNodeType == MASTER_NODE)
        gptp->setCorrectionField(SimTime::ZERO);
    else if (gptpNodeType == BRIDGE_NODE)
    {
        /**************** Correction field calculation *********************************************
         * It is calculated by adding peer delay, residence time and packet transmission time      *
         * correctionField(i)=correctionField(i-1)+peerDelay+(timeReceivedSync-timeSentSync)*(1-f) *
         *******************************************************************************************/
        // gptp->setCorrectionField(correctionField + peerDelay + sentTimeSyncSync - receivedTimeSync);  //  revise it!!! see prev. comment, where is the (1-f),  ???
        gptp->setCorrectionField(SimTime::ZERO);  //  revise it!!! see prev. comment, where is the (1-f),  ???
    }
    gptp->setRateRatio(gmRateRatio);
    packet->insertAtFront(gptp);
    sendPacketToNIC(packet, portId);
}

/*void gPtp::sendPdelayResp(GptpReqAnswerEvent* req)
{
    int portId = req->getPortId();
    auto packet = new Packet("GptpPdelayResp");
    packet->addTag<MacAddressReq>()->setDestAddress(GPTP_MULTICAST_ADDRESS);
    auto gptp = makeShared<GptpPdelayResp>();
    //??? gptp->setSentTime(clock->getClockTime());
    gptp->setRequestingPortIdentity(req->getSourcePortIdentity());
    //gptp->setSequenceId(req->getSequenceId());
    gptp->setRequestReceiptTimestamp(req->getIngressTimestamp());
    packet->insertAtFront(gptp);
    sendPacketToNIC(packet, portId);
    // The sendPdelayRespFollowUp(portId) called by receiveSignal(), when GptpPdelayResp sent
}*/

void gPtp::sendPdelayRespFollowUp(int portId, const GptpPdelayResp* resp)
{
    auto packet = new Packet("GptpPdelayRespFollowUp");
    packet->addTag<MacAddressReq>()->setDestAddress(GPTP_MULTICAST_ADDRESS);
    auto gptp = makeShared<GptpPdelayRespFollowUp>();
   // auto now = clock->getCurrentTime();
    auto now = simTime();
    gptp->setResponseOriginTimestamp(now);
    gptp->setRequestingPortIdentity(resp->getRequestingPortIdentity());
    //gptp->setSequenceId(resp->getSequenceId());
    packet->insertAtFront(gptp);
    sendPacketToNIC(packet, portId);
}

void gPtp::sendPdelayReq()
{
    ASSERT(slavePortId != -1);
    auto packet = new Packet("GptpPdelayReq");
    packet->addTag<MacAddressReq>()->setDestAddress(GPTP_MULTICAST_ADDRESS);
    auto gptp = makeShared<GptpPdelayReq>();
    gptp->setCorrectionField(SimTime::ZERO);
    //save and send IDs
    PortIdentity portId;
    portId.clockIdentity = getId();
    portId.portNumber = slavePortId;
    gptp->setSourcePortIdentity(portId);
    lastSentPdelayReqSequenceId = sequenceId++;
    //gptp->setSequenceId(lastSentPdelayReqSequenceId);
    packet->insertAtFront(gptp);
    //pdelayReqEventEgressTimestamp = clock->getCurrentTime();
    rcvdPdelayResp = false;
    sendPacketToNIC(packet, slavePortId);
}


void gPtp::processSync(Packet *packet, const GptpSync* gptp)
{
    rcvdGptpSync = true;
    //ccc  lastReceivedGptpSyncSequenceId = gptp->getSequenceId();

    peerSentTimeSync = gptp->getOriginTimestamp();  //  this is unfilled in two-step mode
    syncIngressTimestamp = packet->getTag<GptpIngressTimeInd>()->getArrivalClockTime();
}

void gPtp::processFollowUp(Packet *packet, const GptpFollowUp* gptp)
{
    // check: is received the GptpSync for this GptpFollowUp?
    if (!rcvdGptpSync) {
        EV_WARN << "GptpFollowUp arrived without GptpSync, dropped";
        return;
    }
    // verify IDs
   /* ccc if (gptp->getSequenceId() != lastReceivedGptpSyncSequenceId) {
        EV_WARN << "GptpFollowUp arrived with invalid sequence ID, dropped";
        return;
    }*/


    peerSentTimeSync = gptp->getPreciseOriginTimestamp();
    correctionField = gptp->getCorrectionField();
    receivedRateRatio = gptp->getRateRatio();

    synchronize();

    EV_INFO << "############## FOLLOW_UP ################################"<< endl;
    EV_INFO << "RECEIVED TIME AFTER SYNC - " << newLocalTimeAtTimeSync << endl;
    EV_INFO << "ORIGIN TIME SYNC         - " << originTimestamp << endl;
    EV_INFO << "CORRECTION FIELD         - " << correctionField << endl;
    EV_INFO << "PROPAGATION DELAY        - " << peerDelay << endl;

    rcvdGptpSync = false;
}

void gPtp::synchronize()
{
    simtime_t now = simTime();
    //simtime_t origNow = clock->getCurrentTime();
    simtime_t origNow = simTime();
    simtime_t residenceTime = origNow - syncIngressTimestamp;

    //cccemit(timeDifferenceSignal, CLOCKTIME_AS_SIMTIME(origNow) - now);

    /************** Time synchronization *****************************************
     * Local time is adjusted using peer delay, correction field, residence time *
     * and packet transmission time based departure time of Sync message from GM *
     *****************************************************************************/
   // simtime_t newTime = peerSentTimeSync + peerDelay + correctionField + residenceTime;

   // check_and_cast<SettableClock *>(clock.get())->setClockTime(newTime);???还是时钟的问题，要改

    //  computeGmRateRatio:
    gmRateRatio = (origNow - newLocalTimeAtTimeSync) / (syncIngressTimestamp - receivedTimeSync);
    gmRateRatio = 1.0 / gmRateRatio;

    oldLocalTimeAtTimeSync = origNow;
    newLocalTimeAtTimeSync =  simTime();//clock->getCurrentTime();
    receivedTimeSync = syncIngressTimestamp;

    // adjust local timestamps, too
    pdelayReqEventEgressTimestamp += newLocalTimeAtTimeSync - oldLocalTimeAtTimeSync;

    /************** Rate ratio calculation *************************************
     * It is calculated based on interval between two successive Sync messages *
     ***************************************************************************/

    EV_INFO << "############## SYNC #####################################"<< endl;
    EV_INFO << "RECEIVED TIME AFTER SYNC   - " << newLocalTimeAtTimeSync << endl;
    EV_INFO << "RECEIVED SIM TIME          - " << now << endl;
    EV_INFO << "ORIGIN TIME SYNC           - " << peerSentTimeSync << endl;
    EV_INFO << "RESIDENCE TIME             - " << residenceTime << endl;
    EV_INFO << "CORRECTION FIELD           - " << correctionField << endl;
    EV_INFO << "PROPAGATION DELAY          - " << peerDelay << endl;
    //EV_INFO << "TIME DIFFERENCE TO SIMTIME - " << CLOCKTIME_AS_SIMTIME(newLocalTimeAtTimeSync) - now << endl;
    EV_INFO << "RATE RATIO                 - " << gmRateRatio << endl;

    emit(rateRatioSignal, gmRateRatio);
    //emit(localTimeSignal, CLOCKTIME_AS_SIMTIME(newLocalTimeAtTimeSync));
    //emit(timeDifferenceSignal, CLOCKTIME_AS_SIMTIME(newLocalTimeAtTimeSync) - now);
}

void gPtp::processPdelayReq(Packet *packet, const GptpPdelayReq* gptp)
{
    peerRequestReceiptTimestamp = simTime();//clock->getCurrentTime();

    //ccc auto resp = new GptpReqAnswerEvent("selfMsgPdelayResp", GPTP_SELF_REQ_ANSWER_KIND);
    //resp->setPortId(packet->getTag<InterfaceInd>()->getInterfaceId());
    //resp->setIngressTimestamp(packet->getTag<GptpIngressTimeInd>()->getArrivalClockTime());
    //resp->setSourcePortIdentity(gptp->getSourcePortIdentity());
    //resp->setSequenceId(gptp->getSequenceId());

   // scheduleAt(pDelayReqProcessingTime, resp);
}

void gPtp::processPdelayResp(Packet *packet, const GptpPdelayResp* gptp)
{
    // verify IDs
    //if (gptp->getRequestingPortIdentity().clockIdentity != getId() || gptp->getRequestingPortIdentity().portNumber != slavePortId) {
      //  EV_WARN << "GptpPdelayResp arrived with invalid PortIdentity, dropped";
    //    return;
    //}
   /*ccc if (gptp->getSequenceId() != lastSentPdelayReqSequenceId) {
        EV_WARN << "GptpPdelayResp arrived with invalid sequence ID, dropped";
        return;
    }*/

    rcvdPdelayResp = true;
    pdelayRespEventIngressTimestamp = packet->getTag<GptpIngressTimeInd>()->getArrivalClockTime();
    peerRequestReceiptTimestamp = gptp->getRequestReceiptTimestamp();
    peerResponseOriginTimestamp = SimTime::ZERO;
}

void gPtp::processPdelayRespFollowUp(Packet *packet, const GptpPdelayRespFollowUp* gptp)
{
    if (!rcvdPdelayResp) {
        EV_WARN << "GptpPdelayRespFollowUp arrived without GptpPdelayResp, dropped";
        return;
    }
    // verify IDs
   // if (gptp->getRequestingPortIdentity().clockIdentity != getId() || gptp->getRequestingPortIdentity().portNumber != slavePortId) {
    //    EV_WARN << "GptpPdelayRespFollowUp arrived with invalid PortIdentity, dropped";
    //    return;
   // }
   /* if (gptp->getSequenceId() != lastSentPdelayReqSequenceId) {
        EV_WARN << "GptpPdelayRespFollowUp arrived with invalid sequence ID, dropped";
        return;
    }*///ccc

    peerResponseOriginTimestamp = gptp->getResponseOriginTimestamp();

    // computePropTime():
    peerDelay = (gmRateRatio * (pdelayRespEventIngressTimestamp - pdelayReqEventEgressTimestamp) - (peerResponseOriginTimestamp - peerRequestReceiptTimestamp)) / 2.0;

    EV_INFO << "RATE RATIO                       - " << gmRateRatio << endl;
    EV_INFO << "pdelayReqEventEgressTimestamp    - " << pdelayReqEventEgressTimestamp << endl;
    EV_INFO << "peerResponseOriginTimestamp      - " << peerResponseOriginTimestamp << endl;
    EV_INFO << "pdelayRespEventIngressTimestamp  - " << pdelayRespEventIngressTimestamp << endl;
    EV_INFO << "peerRequestReceiptTimestamp      - " << peerRequestReceiptTimestamp << endl;
    EV_INFO << "PEER DELAY                       - " << peerDelay << endl;

    //ccc  emit(peerDelaySignal, CLOCKTIME_AS_SIMTIME(peerDelay));
}

void gPtp::receiveSignal(cComponent *source, simsignal_t signal, cObject *obj, cObject *details)
{
    /*Enter_Method("%s", cComponent::getSignalName(signal));

    if (signal == inet::packetReceivedSignal) {
        auto signal = check_and_cast<cPacket *>(obj);
        auto packet = check_and_cast_nullable<Packet *>(signal->getEncapsulatedPacket());
        if (packet) {
            packet->addTagIfAbsent<GptpIngressTimeInd>()->setArrivalClockTime(clock->getCurrentTime());


        }
    }
    else if (signal == inet::packetSentSignal) {
        auto signal = check_and_cast<cPacket *>(obj);
        auto packet = check_and_cast_nullable<Packet *>(signal->getEncapsulatedPacket());
        if (packet) {
            auto protocol = packet->getTag<PacketProtocolTag>()->getProtocol();
            if (*protocol == Protocol::ethernetPhy) {
                const auto& ethPhyHeader = packet->peekAtFront<physicallayer::EthernetPhyHeader>();
                const auto& ethMacHeader = packet->peekAt<EthernetMacHeader>(ethPhyHeader->getChunkLength());
                if (ethMacHeader->getTypeOrLength() == ETHERTYPE_GPTP) {
                    const auto& gptp = packet->peekAt<GptpBase>(ethPhyHeader->getChunkLength() + ethMacHeader->getChunkLength());
                    int portId = getContainingNicModule(check_and_cast<cModule*>(source))->getInterfaceId();
                    switch (gptp->getMessageType()) {
                        case GPTPTYPE_PDELAY_RESP: {
                            auto gptpResp = dynamicPtrCast<const GptpPdelayResp>(gptp);
                            sendPdelayRespFollowUp(portId, gptpResp.get());
                            break;
                        }
                        case GPTPTYPE_SYNC: {
                            auto gptpSync = dynamicPtrCast<const GptpSync>(gptp);
                            sendFollowUp(portId, gptpSync.get(), clock->getCurrentTime());
                            break;
                        }
                        case GPTPTYPE_PDELAY_REQ:
                            if (portId == slavePortId)
                                pdelayReqEventEgressTimestamp = clock->getCurrentTime();
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }*/
}

}
