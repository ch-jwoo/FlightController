#ifndef __MODULEAHRS__H
#define __MODULEAHRS__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "cmsis_os.h"

#include "freertosVariable.h"
#include "Utils/Freq.h"

namespace FC{

enum AhrsSignal{
	AhrsAccel = 0x1,
	AhrsGyro = 0x2
};

class ModuleAHRS : public Freq<ModuleAHRS>{
public:

	/*
	 *  initialize member variable
	 */
	ModuleAHRS();

	/*
	 *  ModuleAHRS main function
	 *  this function is called by CMSIS task function
	 *	wait signal from accelerometer and gyrometer
	 */
    static void main();

    /*
     *  calculate madgwick
     */
    void oneStep();

    /*
     *  signal to AHRS main function
     *  this function is called by SensorAccel, SensorGyro (peripheral interface)
     */
    static inline void setSignal(enum AhrsSignal signal){
    	switch(signal){
    	case AhrsAccel:
        	osThreadFlagsSet(AHRS_TaskHandle, AhrsAccel);
        	break;
    	case AhrsGyro:
        	osThreadFlagsSet(AHRS_TaskHandle, AhrsGyro);
    	}
    }

	~ModuleAHRS() = default;
	ModuleAHRS& operator=(ModuleAHRS &&other) = delete;
	ModuleAHRS& operator=(const ModuleAHRS &other) = delete;
	ModuleAHRS(ModuleAHRS &&other) = delete;
	ModuleAHRS(const ModuleAHRS &other) = delete;
private:
    /* input */
    struct BodyAccel bodyAccelSub;
    struct BodyAngularVelocity bodyAngularVelocitySub;
    struct BodyMag bodyMagSub;

    /* output */
    struct Attitude attitudePub;
    struct NedAccel nedAccelPub;

    /* used by Madgwick algorithm */
    uint64_t lastUpdate;
    float beta;
    float q0;
    float q1;
    float q2;
    float q3;
    
    /*
     *  Madgwick algorithm
     *  \param		gx, gy, gz		gyro value (rad/s)
     *  \param		ax, ay, az		accel vector (unit is not important)
     *  \param		mx, my, mz		mag vector (unit is not important)
     */
    void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

    /*
     *  calculate acceleration on NED axis
     *  using current roll, pitch, yaw values from madgwick algorithm
     */
    void calNedAccel();

    /*
     *  calculate 1/root(x)
     *  used by madgwick algorithm
     */
    float invSqrt(float x);
};


}
#endif
