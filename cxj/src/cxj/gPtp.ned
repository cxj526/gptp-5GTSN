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

package src.cxj;
import inet.applications.contract.IApp;

simple gPtp like IApp
{
     parameters:
        //@display("i=block/app");
        string clockModule = default(""); // relative path of a module that implements IClock; optional
        string interfaceTableModule;
        string gptpNodeType; // @enum("GptpNodeType"): MASTER_NODE, BRIDGE_NODE, SLAVE_NODE
        string slavePort = default(""); // port for receiving time (empty for MASTER_NODE)
        string masterPorts = default(""); // ports for sending out time (empty for SLAVE_NODE) //暂时先注释
       
        double correctionField @unit(s) = default(0s);
        double syncInterval @unit(s) = default(0.125s);
        double pdelayInterval @unit(s) = default(1s);
        double syncInitialOffset @unit(s) = default(syncInterval);
        double pdelayInitialOffset @unit(s) = default(pdelayInterval);

        // following parameters are used to schedule follow_up and pdelay_resp messages.
        // These numbers must be enough large to prevent creating queue in MAC layer.
        // It means it should be large than transmission time of message sent before
        double pDelayReqProcessingTime @unit(s) = default(8us);  // processing time between arrived PDelayReq and send of PDelayResp
        double followUpInterval @unit(s) = default(7us);

        
        @signal[localTime](type=simtime_t);  // as clocktime_t
        @signal[timeDifference](type=simtime_t);
        @signal[rateRatio](type=double);
        @signal[peerDelay](type=simtime_t);
        @statistic[localTime](record=vector; interpolationmode=linear);
        @statistic[timeDifference](record=vector; interpolationmode=linear);
        @statistic[rateRatio](record=vector; interpolationmode=samplehold);
        @statistic[peerDelay](record=vector; interpolationmode=samplehold);
        @selfMessageKinds(inet48021as::GptpSelfMsgKind);

    gates:
        input socketIn;
        output socketOut;

}