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

package simulations;
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

package simulations;
import src.cxj.gPtpBridge;
import src.cxj.gPtpMaster;
import src.cxj.gPtpSlave;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;

network NetworkDaisyChain
{
    @display("bgb=534,441");
    types:
        channel Ethernet100 extends ned.DatarateChannel
        {
            datarate = 100Mbps;
            delay = 25ns;		// Length of connection is 5 meters
        }
    submodules:
        gPtpBridge0: gPtpBridge {
            @display("p=264,162");
        }
        gPtpBridge1: gPtpBridge {
            @display("p=264,258");
        }
        gPtpBridge2: gPtpBridge {
            @display("p=264,349");
        }
        gPtpMaster: gPtpMaster {
            @display("p=264,55");
        }
        gPtpSlave0: gPtpSlave {
            @display("p=397,101");
        }
        gPtpSlave1: gPtpSlave {
            @display("p=408,182");
        }
        gPtpSlave2: gPtpSlave {
            @display("p=408,259");
        }
        gPtpSlave3: gPtpSlave {
            @display("p=408,375");
        }
        gPtpSlave4: gPtpSlave {
            @display("p=124,375");
        }
        gPtpSlave5: gPtpSlave {
            @display("p=124,298");
        }
        gPtpSlave6: gPtpSlave {
            @display("p=124,205");
        }
        gPtpSlave7: gPtpSlave {
            @display("p=124,94");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=51,33");
        }
    connections:

        gPtpMaster.ethg++ <--> Ethernet100 <--> gPtpBridge0.ethg++;
        gPtpBridge0.ethg++ <--> Ethernet100 <--> gPtpSlave0.ethg++;
        gPtpBridge0.ethg++ <--> Ethernet100 <--> gPtpSlave1.ethg++;
        gPtpBridge0.ethg++ <--> Ethernet100 <--> gPtpSlave7.ethg++;
        gPtpBridge0.ethg++ <--> Ethernet100 <--> gPtpBridge1.ethg++;
        gPtpBridge1.ethg++ <--> Ethernet100 <--> gPtpSlave2.ethg++;
        gPtpBridge1.ethg++ <--> Ethernet100 <--> gPtpSlave6.ethg++;
        gPtpBridge1.ethg++ <--> Ethernet100 <--> gPtpSlave5.ethg++;
        gPtpBridge1.ethg++ <--> Ethernet100 <--> gPtpBridge2.ethg++;
        gPtpBridge2.ethg++ <--> Ethernet100 <--> gPtpSlave3.ethg++;
        gPtpBridge2.ethg++ <--> Ethernet100 <--> gPtpSlave4.ethg++;
}
