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
//import inet48021as.StandardHostAS;
import inet.node.inet.StandardHost;
module gPtpEndstation extends StandardHost
{
    parameters:
        //@display("i=device/pc2;bgb=1274.1749,705.6");
        //clock.typename = default("Clock");
        **.interfaceTableModule = default(absPath(".interfaceTable"));
        
    submodules:
        gptp: gPtp {
            @display("p=680,47");
            //gptpNodeType = default("SLAVE_NODE");
        }
        clock: <default("Clock")> like IClock if typename != "" {
            @display("p=213,115");
        }

    connections:
        gptp.socketOut --> at.in++;
        at.out++ --> gptp.socketIn;
}
