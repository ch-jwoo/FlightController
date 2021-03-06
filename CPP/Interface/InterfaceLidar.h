/*
 * SensorLidar.h
 *
 *  Created on: Aug 21, 2020
 *      Author: cjb88
 */

#ifndef INTERFACE_INTERFACELIDAR_H_
#define INTERFACE_INTERFACELIDAR_H_
#include "main.h"
#include "MsgBus/MsgBus.h"
#include "Utils/Freq.h"

namespace FC {

class InterfaceLidar : public Freq<InterfaceLidar> {
public:
	InterfaceLidar();

	/*
	 *  set distance to ground
	 *  this function called by sensor callback
	 *  \pram[in]		distance		distance to ground in [m]
	 */
	void setDistance(float distance /*[m]*/);

	/*
	 *  calculate reference distance
	 *  this function call when arming vehicle
	 *  after calling this function, the commander must delay som time to setting bias
	 */
	void setRefDistance();

	~InterfaceLidar() = default;
	InterfaceLidar(const InterfaceLidar &other) = delete;
	InterfaceLidar(InterfaceLidar &&other) = delete;
	InterfaceLidar& operator=(const InterfaceLidar &other) = delete;
	InterfaceLidar& operator=(InterfaceLidar &&other) = delete;

private:
	/* subscribe */
	struct Attitude attitudeSub;

	/* publish */
	struct Lidar lidarPub;

	float refDistance;

	bool calRefFlag;
	float avgDistance;
	uint8_t avgIndex;

	uint32_t lastUpdatedMillisec;

	void calAverage(float distance);

	const static uint8_t AVERAGE_SIZE = 20;

	constexpr static float MAX_RADIAN = 0.1745329;		/* 10.0 degree */
	const static uint32_t MINIMUM_TIME_INTERVAL_MILLISEC = 20;		/* max 50hz */
};

extern InterfaceLidar interfaceLidar;

} /* namespace FC */

#endif /* INTERFACE_INTERFACELIDAR_H_ */
