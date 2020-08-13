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

#endif
