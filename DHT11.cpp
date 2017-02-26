#include "Arduino.h"
#include "DHT11.h"

//定义数组
int chr[40] = {0};

//定义接口
int pin ;

//无参构造方法
DHT11::DHT11()
{
	pin = 2;
	//None
}

//有参构造方法,自定义数据接口
DHT11::DHT11(int pin1)
{
	pin = pin1;
}

//初始化数组（需要每次读取温湿度数据之前执行一次）
void DHT11::dump()
{
	readHumitureArray();
}

//获取温度值
int DHT11::readTemp()
{
	return chr[16] * 128 + chr[17] * 64 + chr[18] * 32 + chr[19] * 16 + chr[20] * 8 + chr[21] * 4 + chr[22] * 2 + chr[23];
}

//获取湿度值
int DHT11::readHumi()
{
	return chr[0] * 128 + chr[1] * 64 + chr[2] * 32 + chr[3] * 16 + chr[4] * 8 + chr[5] * 4 + chr[6] * 2 + chr[7];
}

//读取数组数据
bool DHT11::readHumitureArray()
{
	unsigned int loopCnt;
	unsigned long time;

	bgn:
	pinMode(pin,OUTPUT);
	digitalWrite(pin,LOW);
	delay(20);
	digitalWrite(pin,HIGH);
	delayMicroseconds(40);
	digitalWrite(pin,LOW);
	pinMode(pin,INPUT);
	loopCnt = 10000;
	while(digitalRead(pin) != HIGH)
	{
		if (loopCnt-- == 0)
		{
			goto bgn;
		}
	}
	loopCnt = 30000;
	while(digitalRead(pin) != LOW)
	{
		if (loopCnt-- == 0)
		{
			goto bgn;
		}
	}
	for (int i = 0; i < 40; i++)
	{
		while(digitalRead(pin) == LOW){}
		time = micros();
		while(digitalRead(pin) == HIGH){}
		if (micros() - time > 50)
		{
			chr[i] = 1;
		}
		else
		{
			chr[i] = 0;
		}
	}
}