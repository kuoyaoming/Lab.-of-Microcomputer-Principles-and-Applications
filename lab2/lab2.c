#include<reg51.h>
#include<intrins.h>
#define RR(x)_cror_(x,1);
void delayms(unsigned int time);
void main()
{
	P2=0x0f;
	while(1){
		P2=RR(P2);
		delayms(500);
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