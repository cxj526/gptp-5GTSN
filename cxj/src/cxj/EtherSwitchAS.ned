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

import inet.node.ethernet.EtherSwitch;
import inet.applications.contract.IApp;

module EtherSwitchAS extends EtherSwitch
{
    parameters:
        bool hasGptp = default(false);
       
    submodules:
        gptp: <default("gPtp")> like IApp if hasGptp {
            @display("p=808,69");
            gptpNodeType = default("BRIDGE_NODE"); // @enum("gptpNodeType"): MASTER_NODE, BRIDGE_NODE, SLAVE_NODE
        }
        clock: <default(hasGptp ? "Clock" : "")> like IClock if typename != "" {
            @display("p=211,114");
        }
    connections:
        gptp.socketOut --> up.in++;
        up.out++ --> gptp.socketIn;
}
