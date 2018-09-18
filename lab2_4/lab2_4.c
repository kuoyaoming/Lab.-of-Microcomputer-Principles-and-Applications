#include<reg51.h>
#include<intrins.h>
#define RR(x)_cror_(x,1);
void delayms(unsigned int time);
void main()
{
	char tb[]={0xc0,0x50,0x24,0x11,0x48,0x14,0x06,0x01};
	while(1){
		int i;
		for(i=0;i<8;i++){
			P2=~tb[i];
			delayms(500);
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