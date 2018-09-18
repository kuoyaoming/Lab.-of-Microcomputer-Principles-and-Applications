#include<reg51.h>
#include<intrins.h>
#define RR(x)_cror_(x,1);
void delayms(unsigned int time);
void main()
{
	char tb[]={0x81,0x42,0x24,0x18,0x24,0x42,0x81};
	while(1){
		int i;
		for(i=0;i<7;i++){
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