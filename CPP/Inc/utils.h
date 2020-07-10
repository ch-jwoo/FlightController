#ifndef __UTILS_HH
#define __UTILS_HH

uint32_t stm_millis; // rise count in timer interrupt
static uint32_t last_time;

void time_tic(){
	last_time = stm_millis;
}
uint32_t time_toc(){
	return stm_millis - last_time;
}

//class Clock{
//public:
//
//	static uint64_t curTime;
//
//	Clock(){};
//
//	inline void tic(){
//		lastTime = Clock::curTime;
//	}
//
//	inline uint64_t toc(){
//		if(lastTime > Clock::curTime){
//			return (MAX_TIME - lastTime) + Clock::curTime;
//		}
//		return lastTime - Clock::curTime;
//	}
//
//	inline static void update(){
//		Clock::curTime++;
//	}
//
//private:
//	uint64_t lastTime;
//
//	const uint64_t MAX_TIME = 65536; // 2^16
//};
//
//uint64_t Clock::curTime = 0;

#endif
