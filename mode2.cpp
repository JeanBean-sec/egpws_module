#include "egpws.h"
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"

//Mode2 Excessive Terrain Closure

void Mode2A::EvaluateTerrainClosure(float elapsedsincelastcall, double Altitude, double Airspeed) {
	//terrain closure calculation
	double upperaltitudeceiling = 1650.00;

	if (Airspeed > 220.00 && Altitude < 310.00) {
		upperaltitudeceiling = 1650.00 - (8.888 * (Airspeed - 220.00));
	}
	else if (Airspeed >= 310.00) {
		upperaltitudeceiling = 2450.00;
	}

	double rateofterrainclosure = (Altitude - LastAltitude) / elapsedsincelastcall;
	LastAltitude = Altitude;

	if (Altitude > 200.00 && Altitude < upperaltitudeceiling) {
		double threshold = (Altitude + 1230.00) / 0.354;
		if (rateofterrainclosure > threshold && Altitude <= upperaltitudeceiling) {
			Terrain = true;
		}
		else {
			Terrain = false;
		}
	}
}

void Mode2A::EvaluatePullUp(float elapsedsincelastcall, double Altitude, double Airspeed) {
	//this is for pullup calculation
}


Mode2A::Mode2A() {
	//this is for the alert states and misc variables
	LastAltitude = 0.0;
	Terrain = false;
	Pullup = false;
}

void Mode2A::EvaluateMode(float elapsedsincelastcall, double Altitude, double Airspeed) {
	//this is for the alerts
}