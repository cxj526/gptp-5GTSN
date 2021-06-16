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
module gPtpMaster extends gPtpEndstation
{
    parameters:
    	// @display("i=device/pc2;bgb=1274.1749,744.975");
    	forwarding = default(false);  // disable routing by default
    	networkLayer.proxyARP = default(false);
       	gptp.gptpNodeType = "MASTER_NODE";// @enum("gptpNodeType"): MASTER_NODE, BRIDGE_NODE, SLAVE_NODE  

    
}
