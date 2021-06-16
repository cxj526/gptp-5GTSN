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

#include "Clock.h"

namespace cxj{



Define_Module(Clock);

//simsignal_t gPtp::localTimeSignal = cComponent::registerSignal("localTime");

void Clock :: initialize(){
    lastAdjustedClock = 0;
    lastSimTime = 0;
    clockDrift = par("clockDrift");
}
/* Return drifted current time based on last adjusted time */
simtime_t Clock::getCurrentTime()
{
    simtime_t duration = simTime() - lastSimTime;
    simtime_t currentTime = lastAdjustedClock + duration + duration.dbl()*clockDrift.dbl()/1000000;

    return currentTime;
}

/* Return drift for only the given value */
simtime_t Clock::getCalculatedDrift(simtime_t value)
{
    simtime_t drift = clockDrift*value.dbl()/1000000;

    return drift;
}

/* Adjust time based on last adjusted time */
void Clock::adjustTime(simtime_t value)
{
    lastAdjustedClock = value;
    lastSimTime = simTime();
}

}//inet48021as

