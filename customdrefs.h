#include "XPLMDataAccess.h"


//setup datarefs externally so they can be used in the main files

//SINKRATE
extern XPLMDataRef drSinkRate;
extern int drSinkRateValue;

inline int GetSinkRateCB(void* inRefcon) {
	return drSinkRateValue;
}
inline void SetSinkRateCB(void* inRefcon, int inValue) {
	drSinkRateValue = inValue;
}

//PULLUP
extern XPLMDataRef drPullUp;
extern int drPullUpValue;

inline int GetPullUpCB(void* inRefcon) {
	return drPullUpValue;
}

inline void SetPullUpCB(void* inRefcon, int inValue) {
	drPullUpValue = inValue;
}



inline static void customdatarefinitialization() {
	// DataRef setup for sinkrate activation
	drSinkRate = XPLMRegisterDataAccessor(
		"cereza/egpws/sinkrate",
		xplmType_Int,
		1,
		GetSinkRateCB, SetSinkRateCB,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL);
	drSinkRate = XPLMFindDataRef("cereza/egpws/sinkrate");
	XPLMSetDatai(drSinkRate, 0); // Initialize to 0 (inactive)
	// DataRef setup for pullup activation
	drPullUp = XPLMRegisterDataAccessor(
		"cereza/egpws/pullup",
		xplmType_Int,
		1,
		GetPullUpCB, SetPullUpCB,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL);
	drPullUp = XPLMFindDataRef("cereza/egpws/pullup");
	XPLMSetDatai(drPullUp, 0); // Initialize to 0 (inactive)
}