#ifndef DHT11_h
#define DHT11_h

#include "Arduino.h"

class DHT11
{
public:

	DHT11(void);			//默认数据接口2

	DHT11(int pin);			//用户自定义数据接口

	static int	readTemp();	//获取温度值

	static int	readHumi();	//获取湿度值

	static void	dump();		//初始化数组（需要每次读取温湿度数据之前执行一次）

private:

	static bool readHumitureArray();	//读取数组数据
};

#endif