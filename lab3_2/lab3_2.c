#include <REGX51.H>
void delayms(unsigned int time);
char keypad(void);
void gg(unsigned int a);
unsigned char code seg7[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,//0~9
													 0x89,0xbf,0x6e,0x9d,0xf6,0xff};//+,-,*,/,=," "
unsigned int dd[]={15,15,15,15,15,15,15,15,15,15};

int ans;

main(){
	unsigned int i,j,k,m=1;
	while(1){
		P1=0;
		for(i=0;i<8;i++){
			j=dd[i];
			P2=~seg7[j];
			delayms(4);
			P1++;
		}
		k=keypad();
		switch(m){
			case 1:
				if(k>=0&&k<10){
					dd[0]=k;
					ans=k;
					m++;
				}
				break;
			case 2:
				if(k>9&&k<14){
					dd[1]=k;
					m++;
				}
				break;
			case 3:
				if(k>=0&&k<10){
					dd[2]=k;
					m++;
				}
				break;
			case 4:
				if(k>9&&k<14){
					dd[3]=k;
					m++;
				}
				break;
			case 5:
				if(k>=0&&k<10){
					dd[4]=k;
					m++;
				}
				break;
			case 6:
				if(k==15){
					dd[5]=14;
					gg(1);
					gg(3);
					if(ans>9){
						dd[6]=ans/10;
						dd[7]=ans%10;
					}else{
						dd[7]=ans;
					}
					m++;
				}
				break;			
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
void gg(unsigned int a){

	switch(dd[a]){
		case 10:
			ans=ans+dd[a+1];
			break;
		case 11:
			ans=ans-dd[a+1];
			break;
		case 12:
			ans=ans*dd[a+1];
			break;
		case 13:
			ans=ans/dd[a+1];
			break;
	}
}
char keypad(void){
  char key=0xff;

  P0=0xef;
  if(P0_0==0)  key=0;
  if(P0_1==0)  key=1;
  if(P0_2==0)  key=2;
  if(P0_3==0)  key=3;

  P0=0xdf;
  if(P0_0==0)  key=4;
  if(P0_1==0)  key=5;
  if(P0_2==0)  key=6;
  if(P0_3==0)  key=7;

  P0=0xbf;
  if(P0_0==0)  key=8;
  if(P0_1==0)  key=9;
  if(P0_2==0)  key=10;
  if(P0_3==0)  key=11;

  P0=0x7f;
  if(P0_0==0)  key=12;
  if(P0_1==0)  key=13;
  if(P0_2==0)  key=14;
  if(P0_3==0)  key=15;

  return key;

} 