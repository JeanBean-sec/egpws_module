#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "egpws.h"


//Mode1 Excessive Descent //always active

void Mode1::EvaluateSinkRate(double Altitude, double Drate) {
    {
        // Mode 1 Upper Band: 1000ft to 2450ft AGL
        if (Altitude > 1000.00 && Altitude <= 2450.00) {
            double threshold = -1.0 * ((Altitude + 1429.00) / 0.7749);
            // Triggers if descending FASTER (more negative) than the threshold
            SinkRate = (Drate <= threshold);
            if (Drate <= threshold)
                XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 1);
			else {
                XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 0);
			}
        }
        // Mode 1 Lower Band: 50ft to 1000ft AGL
        else if (Altitude >= 50.00 && Altitude <= 1000.00) {
            double threshold = -1.0 * ((Altitude + 481.50) / 0.4727);
            SinkRate = (Drate <= threshold);
            if (Drate <= threshold)
                XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 1);
            else {
                XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 0);
            }
        }
        // Outside EGPWS Mode 1 limits
        else {
            SinkRate = false;
            XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 0);
        }   
    }
}

void Mode1::EvaluatePullUp(double Altitude, double Drate) {
    // Mode 1 Upper Band: 1000ft to 2450ft AGL
    if (Altitude > 1000.00 && Altitude <= 2450.00) {
        double threshold = -1.0 * ((Altitude + 400.00) / 0.40);
        Pullup = (Drate <= threshold);
        if (Drate <= threshold) {
            XPLMSetDatai(XPLMFindDataRef("cereza/egpws/pullup"), 1);
			XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 0);
        }
        else {
            XPLMSetDatai(XPLMFindDataRef("cereza/egpws/pullup"), 0);
        }
    }
	//Lower Band: 485ft to 1000ft AGL
    else if (Altitude >= 485.00 && Altitude <= 1000.00) {
        double threshold = -1.0 * ((Altitude + 400.00) / 0.481);
        Pullup = (Drate <= threshold);
        if (Drate <= threshold) {
            XPLMSetDatai(XPLMFindDataRef("cereza/egpws/pullup"), 1);
			XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 0);
        }
        else {
            XPLMSetDatai(XPLMFindDataRef("cereza/egpws/pullup"), 0);
        }
    }
	//Lowest Band: 50ft to 485ft AGL
    else if (Altitude >= 50.00 && Altitude < 485.00) {
        double threshold = -1.0 * ((Altitude + 400.00) / 0.216);
        Pullup = (Drate <= threshold);
        if (Drate <= threshold) {
            XPLMSetDatai(XPLMFindDataRef("cereza/egpws/pullup"), 1);
			XPLMSetDatai(XPLMFindDataRef("cereza/egpws/sinkrate"), 0);
        }
        else {
            XPLMSetDatai(XPLMFindDataRef("cereza/egpws/pullup"), 0);
		}
	}
    else {
        Pullup = false;
        XPLMSetDatai(XPLMFindDataRef("cereza/egpws/pullup"), 0);
    }
}

Mode1::Mode1() {
    WasSinkRate = false;
    SinkRate = false;
    Pullup = false;
}


void Mode1::EvaluateMode(double Altitude, double Drate) {
    EvaluateSinkRate(Altitude, Drate);
	EvaluatePullUp(Altitude, Drate);
    if (Pullup) {
        //speak "Pull Up"
    }
    else if (SinkRate && !WasSinkRate) {
		//speak "Sink Rate"
    }
    WasSinkRate = SinkRate;
};

