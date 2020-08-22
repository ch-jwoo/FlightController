#ifndef __SENSORBARO__H
#define __SENSORBARO__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "Usec.h"
#include "Utils/Freq.h"

#include "printf.h"

namespace FC{

class InterfaceBaro : public Freq<InterfaceBaro>{
public:
	InterfaceBaro()
	: barometerPub{0, }
	, seaLevelPressure(1013.25)
	, pressure(0)
	, temperature(0)
	, altitude(0)
	, refAltitude(0)
	{}


    void setBaro(float pressure/*[hPa]*/, float temperature/*[degC]*/);

    /*
     *  set sea level pressure
     *  \param[in]		altitude		sea level altitude
     */
    void setSeaLevelPressure(float altitude);

    /*
     *  set reference altitude to current barometer altitude
     */
    void setRefAltitude();

private:
    struct Barometer barometerPub;

    float seaLevelPressure;
    float pressure;
    float temperature;

    float altitude;
    float refAltitude;


    /*
     *  calculate the altitude (in meters) from the specified atmospheric
     *  pressure (in hPa), and sea level pressure (in hPa)
     *  \param[in]		seaLevel		sea level pressure in hPa
     *  \param[in]		pressure		current pressure in hPa
     *  \return altitude
     */
    float calAltitude(float seaLevel, float pressure);

    /*
     *  Calculate the pressure at sea level (in hPa) from specified altitude (in meter),
     *  and atmospheric pressure (in hPa)
     *  \param[in]		altitude		current altitude
     *  \param[in]		pressure		current pressure
     *  \return the pressure at sea level in hPa
     */
    float calSeaLevelPressure(float altitude, float pressure);

};

extern InterfaceBaro interfaceBaro;


}


#endif
