#ifndef __MODULEAHRS__H
#define __MODULEAHRS__H

#include <MsgBus/MsgBus.h>
#include <MsgBus/MsgType.h>
#include "cmsis_os.h"

#include "freertosVariable.h"
#include "Utils/Freq.h"
#include "Module/ModuleAttitudeController.h"

namespace FC{

enum AhrsSignal{
	AHRS_fromAccel = 0x1,
	AHRS_fromGyro = 0x2
};

class ModuleAHRS : public Freq<ModuleAHRS>{
public:

	/*
	 *  initialize member variable
	 */
	ModuleAHRS();

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
    	case AHRS_fromAccel:
        	osThreadFlagsSet(AHRS_TaskHandle, AHRS_fromAccel);
        	break;
    	case AHRS_fromGyro:
        	osThreadFlagsSet(AHRS_TaskHandle, AHRS_fromGyro);
    	}
    }

	/*
	 *  ModuleAHRS main function
	 *  this function is called by CMSIS task function
	 *	wait signal from accelerometer and gyrometer
	 */
    static void main(){
    	ModuleAHRS moduleAHRS;
    	uint8_t cnt = 0;
    	while(1){
    		/* wait accel, gyro value set */
//    		osThreadFlagsWait(0x3U, osFlagsWaitAll, osWaitForever);
    		moduleAHRS.oneStep();
    		if(cnt>4){
        		ModuleAttitudeController::setSignal(AC_fromAHRS);		/* 200hz */
        		cnt = 0;
    		}

    		cnt++;
    		osDelay(1);			/* 1000hz */
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
