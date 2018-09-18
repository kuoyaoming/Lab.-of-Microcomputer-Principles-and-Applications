#include <REGX51.H>
#include <stdio.h>
#define RS P1_0
#define RW P1_1
#define E  P1_2
#define DB P2
#define DBPORT P2

void init(void);
void LCD_CMD(char cmd);
void LCD_DATA(char data1);
void DISP_Int(char addr1, int v1);
void DISP_Str(char addr1,char *str);
void wrins(char instruction);
void delayms(unsigned int time);
char keypad(void);
unsigned int a1,a2,a3,a4,g1,g2,g3,g4,at,gt,k=99;
unsigned int m=1;
main(){
	init();
	LCD_CMD(0x3f);
	LCD_CMD(0xe);
	LCD_CMD(0x1);
	delayms(1);
	LCD_CMD(0x80);
	while(1){
		k=keypad();
		switch(m){
			case 1:
				if(k>=0&&k<10){
					a1=k;
					delayms(500);
					DISP_Int(0x80,a1);
					m++;
					}
				break;
			case 2:
				if(k>=0&&k<10){
					a2=k;
					delayms(500);
					DISP_Int(0x81,a2);
					m++;
				}
				break;
			case 3:
				if(k>=0&&k<10){
					a3=k;
					delayms(500);
					DISP_Int(0x82,a3);
					m++;
				}
				break;
			case 4:
				if(k>=0&&k<10){
					a4=k;
					delayms(500);
					DISP_Int(0x83,a4);
					m++;
					delayms(1000);
				}
				break;
			case 5:
				LCD_CMD(0x1);
				delayms(1);
				LCD_CMD(0x80);
				if(k>=0&&k<10){
					g1=k;
					delayms(500);
					DISP_Int(0x80,g1);
					m++;
				}
				break;
			case 6:
				if(k>=0&&k<10){
					g2=k;
					delayms(500);
					DISP_Int(0x81,g2);
					m++;
				}
				break;
			case 7:
				if(k>=0&&k<10){
					g3=k;
					delayms(500);
					DISP_Int(0x82,g3);
					m++;
				}
				break;
			case 8:
				if(k>=0&&k<10){
					g4=k;
					delayms(500);
					DISP_Int(0x83,g4);
					at=a1*1000+a2*100+a3*10+a4;
					gt=g1*1000+g2*100+g3*10+g4;
					if(at>gt){
						DISP_Str(0x84,">");
						delayms(1000);
						m=5;
					}else if(at<gt){
						DISP_Str(0x84,"<");
						delayms(1000);
						m=5;
					}else{
						m++;
						DISP_Str(0x84,"OK");
					};
				}
				break;	
		}
	}
}
void DISP_Int(char addr1, int v1){
	LCD_CMD(addr1);
	LCD_DATA(v1+0x30);
}
void DISP_Str(char addr1,char *str){
	LCD_CMD(addr1);
	while(*str != 0)
		LCD_DATA(*str++);
}
void LCD_CMD(char cmd){
	char i;
	DBPORT=cmd;
	RS=0; RW=0; E=1;
	for(i=0;i<40;i++);
	RS=0; RW=0; E=0;
}
void LCD_DATA(char data1){
	char i;
	DBPORT=data1;
	RS=1; RW=0; E=1;
	for(i=0;i<40;i++);
	RS=1; RW=0; E=0;
}
void init(void){
  delayms(30);
  wrins(0x38);
  wrins(0x38);
  wrins(0x38);
  wrins(0x38);
  wrins(0x08);
  wrins(0x01);
  wrins(0x06);
  wrins(0x0c);
}
void wrins(char instruction){
  RS=0;
  RW=0;
  E=0;
  delayms(1);
  E=1;
  DB=instruction;
  delayms(1);
  E=0;
  delayms(8);
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