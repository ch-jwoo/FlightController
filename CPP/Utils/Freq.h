/*
 * Freq.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef MODULE_FREQ_H_
#define MODULE_FREQ_H_

namespace FC{

template<typename T>
class Freq {
public:
	static uint16_t freqCnt;

	static uint16_t checkFreq(){
		uint16_t res = freqCnt;
		freqCnt = 0;
		return res;
	}

	Freq() = default;
	~Freq() = default;
	Freq(const Freq &other) = delete;
	Freq(Freq &&other) = delete;
	Freq& operator=(const Freq &other) = delete;
	Freq& operator=(Freq &&other) = delete;
};

template<typename T>
uint16_t Freq<T>::freqCnt = 0;

}
#endif /* MODULE_FREQ_H_ */
