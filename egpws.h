#pragma once

typedef enum {
    ACTIVE = 1,
    INACTIVE = 2,
} ModeState;

class Mode1 {
private:

    bool WasSinkRate;
    bool SinkRate;
    bool Pullup;

    void EvaluateSinkRate(double Altitude, double Drate);
    void EvaluatePullUp(double Altitude, double Drate);

public:
    Mode1();
	void EvaluateMode(double Altitude, double Drate);
};

class Mode2A {
private:

    double LastAltitude;
    bool Terrain;
    bool Pullup;

    void EvaluateTerrainClosure(float elapsedsincelastcall, double Altitude, double Airspeed);
	void EvaluatePullUp(float elapsedsincelastcall, double Altitude, double Airspeed);

public:
	Mode2A();
	void EvaluateMode(float elapsedsincelastcall, double Altitude, double Airspeed);
};

class Mode2B {};

class Mode3 {};

class Mode4 {};

class Mode5 {};

class Mode6 {};

class Mode7 {};