
// VFD.h, vacuum fluroescent display driver for Samsung HCS-12SS59T, V0.9 171112 qrt@qland.de

#ifndef _VFD_h
#define _VFD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>							

#define SPIPARS					2000000, LSBFIRST, SPI_MODE3


#define VFD_DCRAM_WR			0x10		// ccccaaaa dddddddd dddddddd ..
#define VFD_CGRAM_WR			0x20		// "
#define VFD_ADRAM_WR			0x30		// ccccaaaa ******dd ******dd ..
#define VFD_DUTY				0x50		// ccccdddd
#define VFD_NUMDIGIT			0x60		// "
#define VFD_LIGHTS				0x70		// cccc**dd

#define LINORM					0x00		// normal display
#define LIOFF					0x01		// lights OFF
#define LION					0x02		//        ON

#define NUMDIGITS				12			// display digit width
#define BUFSIZE					100			// display/scroll buffer

const int Pin_VFD_RESET		=	D0;			// VFD _RESET
const int Pin_VFD_VDON		=	D2;			//     _VDON Vdisp 0=ON 1=OFF
const int Pin_VFD_CS		=	D1;			//     _CS   chip select, SPI SS

class VFD
{
public:
	int16_t scrLen;
	int16_t scrPos;
	int16_t scrMode;

	void init();
	void supplyOn();
	void supplyOff();
	void write(char* text);
	void display();
  void setDuty(int duty);

protected:

private:
	char buf[BUFSIZE];

	void select(int pin);
	void deSelect(int pin);
	void sendCmd(char cmd, char arg);
	void sendCmdSeq(char cmd, char arg);
	void sendChar(char c);
  void sendRawChar(char c);
	char getCode(char c);
};

extern VFD Vfd;

#endif
