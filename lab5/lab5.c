#include <REGX51.H>
#include <string.h>
#define RS P1_0
#define RW P1_1
#define E  P1_2
#define DB P2
#define DBPORT P2

void init(void);
void wrcgram(void);
void position(char line,column);
void LCD_CMD(char cmd);
void LCD_DATA(char data1);
void wrins(char instruction);
void display(char *string);
void wrdata(char d);	
void delayms(unsigned int time);
void DISP_Str(char addr1,char *str);
void RL_Str(char addr1,char *str,char offset);
void RL_Str2(char addr2,char *str2,char offest2);

code char pattern[]={0x00,0x18,0x08,0x08,0x08,0x08,0x08,0x18,0x1f,0x00,0x0e,0x11,0x11,0x0e,0x00,0x1f,0x00,0x03,0x02,0x02,0x02,0x02,0x02,0x03};
code char string1[]={0x0a,0x09,0x08,0x00};
code char string2[]={"b10502007"};
code char string3[]={"INT0 happens      "};
code char string4[]={"INT1 happens      "};
char str_display[16];
int x=1;
int z,j,k;
int j_temp,k_temp;
int cnt;

void main(void){
  TCON=5;
  IE=0x85;
  PX0=1;
  init();
  wrcgram();
  
  while(1){
  	for(z=0;z<strlen(string2);z++){
		wrins(0x01);
		delayms(1);
		RL_Str(0x80,string2,0);
		delayms(500);
		}
  }
}
void EXINT0(void) interrupt 0{
	cnt=0;
	if(j_temp>=strlen(string3)-1)
		j_temp=0;
	for(j=j_temp;j<strlen(string3);j++){
		wrins(0x01);
		delayms(1);
		RL_Str(0x80,string3,j);
		delayms(500);
		if(cnt<4){
			cnt++;
		}else {
			j_temp=j;
			break;
		}
	}				    
}
void EXINT1(void) interrupt 2{
	cnt=0;
	if(k_temp>=strlen(string4)-1)
		k_temp=0;
	for(k=k_temp;j<strlen(string4);k++){
		wrins(0x01);
		delayms(1);
		RL_Str(0x80,string4,k);
		delayms(500);
		if(cnt<4){
			cnt++;
		}else {
			k_temp=k;
			break;
		}
	}
}
void RL_Str(char addr1,char *str,char offset){
	char i;
	char *start=str;
	str+=offset;
	LCD_CMD(addr1);
	while(*str !=0)
		LCD_DATA(*str++);
	for(i=0;i<offset;i++)
		LCD_DATA(start[i]);
}
void RL_Str2(char addr2,char *str2,char offset2){
	char i2;
	char *start2=str2;
	str2+=offset2;
	LCD_CMD(addr2);
	while(*str2!=0)
		LCD_DATA(*str2++);
	for(i2=0;i2<offset2;i2++)
		LCD_DATA(start2[i2]);
}
void RR_Str(char addr1,char *str,char offset){
	char i;
	char *start=str;
	LCD_CMD(addr1);
	str+=offset;
	while(*str !=0)
		LCD_DATA(*str++);
	for(i=0;i<20-offset;i++)
		LCD_DATA(start[i]);
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
void wrcgram(void){
  char m;
  wrins(0x40);
  for(m=0; m<24; m++ )
		wrdata(pattern[m]);
}
void position(char line,column){
  unsigned char instruction;
  line--;
  column--;
  instruction=0x80+(0x40*line + column);
  wrins(instruction);
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
void display(char *string){
  char k=0;
  while(string[k] !=0x00 )
   {
     wrdata(string[k]);
     k++;
   }
}
void wrdata(char d){
  RS=1;
  RW=0;
  E=0;
  delayms(1);
  E=1;
  DB=d;
  delayms(1);
  E=0;
  delayms(1);
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