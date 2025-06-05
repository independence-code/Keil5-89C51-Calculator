#include <REGX52.H>
#include <DELAY.H>
sbit dula=P2^6;     
sbit wela=P2^7;    
unsigned char code nixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7c,0x39,0x5e,0x79,0x71};

void nixie(unsigned int Location,unsigned int Number)
{
	switch(Location) 
	{
		case 1:wela=1;P0=0xFE;wela=0;break; 
    case 2:wela=1;P0=0xFD;wela=0;break;
		case 3:wela=1;P0=0xFB;wela=0;break;
		case 4:wela=1;P0=0xF7;wela=0;break;
		case 5:wela=1;P0=0xEF;wela=0;break;
		case 6:wela=1;P0=0xDF;wela=0;break;
		
	}
    
    dula=1;
	  P0=nixieTable[Number];
    dula=0;
    delay(1);
    P0=0Xff;
} 