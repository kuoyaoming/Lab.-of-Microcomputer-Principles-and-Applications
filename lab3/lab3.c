#include <reg51.h>
void delayms(unsigned int time);
unsigned char code seg7[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
													 0x89,0xbf,0xf6,0xff};//0~9,H,-,=," "
unsigned int code dd[]={2,10,3,12,5,13,13,13,13,13};


main(){
	int i,j;
	while(1){
		P1=0;
		for(i=0;i<8;i++){
			j=dd[i];
			P2=~seg7[j];
			delayms(5);
			P1++;
		}
	}
}
void delayms(unsigned int time){
  unsigned int n;
  while(time>0)
   {
     n=120;
     while(n>0)  n--;
     time--;
   }
}