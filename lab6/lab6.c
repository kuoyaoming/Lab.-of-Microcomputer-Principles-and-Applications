#include <REGX51.H>
#include <stdio.h>

#define RS P1_0
#define RW P1_1
#define E  P1_2
#define DB P2
#define DBPORT P2

char keypad(void);
void init(void);
void clock(void);
void Dater(void);
void state(void);
void Date_init(void);
void Time_init(void);
void LCD_CMD(char cmd);
void LCD_DATA(char data1);
void wrins(char instruction);
void display(char *string);
void wrdata(char d);	
void delayms(unsigned int time);
void DISP_Str(char addr1,char *str);
void DISP_Int(char addr1, int v1);
void RL_Str(char addr1,char *str,char offset);
void RL_Str2(char addr2,char *str2,char offest2);
void dd_d(void);
void dd_t(void);
void dd_ts(void);
void set_DT();

int second0,second1; 
int minute0,minute1; 
int hour0,hour1;    
int day0,day1; 
int month0,month1; 
int year0,year1,year2,year3; 
int date; 
int small_mon,leap_year; 
int counter,cycle;
char aa;
int tt,yy,uu;

main(){
  init();
  Date_init();
  Time_init();
	set_DT();
  while(1){
		if(keypad()==3)set_DT();
		clock();
		dd_d();
		dd_t();
		if(day0+day1*10==0)day0=1;
		if(month0+month1*10==0)month0=1;
		delayms(1000);
		
  }
}
void set_DT(){
	int p=1;
	int out=1;
	while(1){
		aa=keypad();
		if(aa==4){
			p++;
		}else if(aa==6){
			p--;
		}else if(p>14){
			p=1;
		}else if(p<1){
			p=14;
		}
		if(p==1){
			DISP_Str(0xcf," ");
			if(aa==1){
				second0++;
				if(second0>9)second0=0;
			}else if(aa==9){
				second0--;
				if(second0<0)second0=9;
			}
		}
		else if(p==2){
			DISP_Str(0xce," ");
			if(aa==1){
				second1++;
				if(second1>5)second1=0;
			}else if(aa==9){
				second1--;
				if(second1<0)second1=5;
			}
		}
		else if(p==3){
			DISP_Str(0xcc," ");
			if(aa==1){
				minute0++;
				if(minute0>9)minute0=0;
			}else if(aa==9){
				minute0--;
				if(minute0<0)minute0=9;
			}
		}
		else if(p==4){
			DISP_Str(0xcb," ");
			if(aa==1){
				minute1++;
				if(minute1>5)minute1=0;
			}else if(aa==9){
				minute1--;
				if(minute1<0)minute1=5;
			}
		}
		else if(p==5){
			DISP_Str(0xc9," ");
			if(aa==1){
				hour0++;
				if(hour1==2){
					if(hour0>3)hour0=0;
				}else	if(hour0>9)hour0=0;
			}else if(aa==9){
				hour0--;
				if(hour0<0)hour0=9;
			}
		}
		else if(p==6){
			DISP_Str(0xc8," ");
			if(aa==1){
				hour1++;
				if(hour1>2)hour1=0;
			}else if(aa==9){
				hour1--;
				if(hour1<0)hour1=2;
			}
		}
		else if(p==7){
			DISP_Str(0x8e," ");
			if(aa==1){
				day0++;
				if(day0>9)day0=0;
			}else if(aa==9){
				day0--;
				if(day0<1)day0=0;
			}
		}
		else if(p==8){
			DISP_Str(0x8d," ");
			if(aa==1){
				day1++;
				if(day1>3)day1=0;
			}else if(aa==9){
				day1--;
				if(day1<0)day1=3;
			}
		}
		else if(p==9){
			DISP_Str(0x8b," ");
			if(aa==1){
				month0++;
				if(month0>9)month0=1;
			}else if(aa==9){
				month0--;
				if(month0<0)month0=9;
			}
		}
		else if(p==10){
			DISP_Str(0x8a," ");
			if(aa==1){
				month1++;
				if(month1>1)month1=0;
			}else if(aa==9){
				month1--;
				if(month1<0)month1=1;
			}
		}
		else if(p==11){
			DISP_Str(0x88," ");
			if(aa==1){
				year0++;
				if(year0>9)year0=0;
			}else if(aa==9){
				year0--;
				if(year0<0)year0=9;
			}
		}
		else if(p==12){
			DISP_Str(0x87," ");
			if(aa==1){
				year1++;
				if(year1>9)year1=0;
			}else if(aa==9){
				year1--;
				if(year1<0)year1=9;
			}
		}
		else if(p==13){
			DISP_Str(0x86," ");
			if(aa==1){
				year2++;
				if(year2>9)year2=0;
			}else if(aa==9){
				year2--;
				if(year2<0)year2=9;
			}
		}
		else if(p==14){
			DISP_Str(0x85," ");
			if(aa==1){
				year3++;
				if(year3>9)year3=0;
			}else if(aa==9){
				year3--;
				if(year3<0)year3=9;
			}
		}
		tt=day0+day1*10;
		yy=month0+month1*10;
		uu=year3*1000+year2*100+year1*10+year0;
		if(hour1*10+hour0>23){
			hour1=2;
			hour0=3;
		}
		if(day1*10+day0>31){
			day1=3;
			day0=1;
		}
		if(month1*10+month0>12){
			month1=1;
			month0=2;
		}
		if(uu%400==0||(uu%4==0&&uu%100!=0)){
			//29day
		}else{
			//28day
		}
		delayms(200);
		dd_ts();
		delayms(200);
		if(keypad()==7){
			break;
		}
	}
}
void dd_d(){
	DISP_Str(0x80,"A.D.");
	DISP_Int(0x85,year3);
	DISP_Int(0x86,year2);
	DISP_Int(0x87,year1);
	DISP_Int(0x88,year0);
	DISP_Str(0x89,"Y");
	DISP_Int(0x8a,month1);
	DISP_Int(0x8b,month0);
	DISP_Str(0x8c,"M");
	DISP_Int(0x8d,day1);
	DISP_Int(0x8e,day0);
	DISP_Str(0x8f,"D");
	if(((year3*1000+year2*100+year1*10)/1000)==0)DISP_Str(0x85," ");
	if(((year3*1000+year2*100+year1*10)/100)==0)DISP_Str(0x86," ");
	if(((year3*1000+year2*100+year1*10)/10)==0)DISP_Str(0x87," ");
	if(month1==0)DISP_Str(0x8a," ");
	if(day1==0)DISP_Str(0x8d," ");
}
void dd_t(){
	if((hour0 + hour1 * 10)==0){
		DISP_Str(0xc0,"A.M.");
		DISP_Int(0xC8,1);
	  DISP_Int(0xC9,2);
	}
	if((hour0 + hour1 * 10)<12&&(hour0 + hour1 * 10)>0){
		DISP_Str(0xc0,"A.M.");
		DISP_Int(0xC8,hour1);
	  DISP_Int(0xC9,hour0);
	}
	if((hour0 + hour1 * 10)==12){
		DISP_Str(0xc0,"P.M.");
		DISP_Int(0xC8,hour1);
	  DISP_Int(0xC9,hour0);
	}
	if((hour0 + hour1 * 10)>12){
		DISP_Str(0xc0,"P.M.");
		DISP_Int(0xC8,hour1 - 1);
	  DISP_Int(0xC9,hour0 - 2);
	}
	DISP_Str(0xCA,":");
	DISP_Int(0xCB,minute1);
	DISP_Int(0xCC,minute0);
	DISP_Str(0xCD,":");
	DISP_Int(0xCE,second1);
	DISP_Int(0xCF,second0);
}
void dd_ts(){
//	if(day1==3&&day0>1)day0=0;
//	if(month1==1&&month0>2)month0=0;
	
	DISP_Str(0x80,"A.D.");
	DISP_Int(0x85,year3);
	DISP_Int(0x86,year2);
	DISP_Int(0x87,year1);
	DISP_Int(0x88,year0);
	DISP_Str(0x89,"Y");
	DISP_Int(0x8a,month1);
	DISP_Int(0x8b,month0);
	DISP_Str(0x8c,"M");
	DISP_Int(0x8d,day1);
	DISP_Int(0x8e,day0);
	DISP_Str(0x8f,"D");
	if((hour0 + hour1 * 10)<12){
		DISP_Str(0xc0,"A.M.");
	}
	if((hour0 + hour1 * 10)==12){
		DISP_Str(0xc0,"P.M.");
	}
	if((hour0 + hour1 * 10)>12){
		DISP_Str(0xc0,"P.M.");
	}
	DISP_Int(0xC8,hour1);
	DISP_Int(0xC9,hour0);
	DISP_Str(0xCA,":");
	DISP_Int(0xCB,minute1);
	DISP_Int(0xCC,minute0);
	DISP_Str(0xCD,":");
	DISP_Int(0xCE,second1);
	DISP_Int(0xCF,second0);
}
void Date_init(){ 
  date = 1; 
  day0 = 8; 
  day1 = 0; 
  month0 = 1; 
  month1 = 0; 
  year0 = 8; 
  year1 = 1; 
  year2 = 0; 
  year3 = 2; 
}
void Time_init(){ 
  second0 = 8; 
  second1 = 5; 
  minute0 = 9; 
  minute1 = 5; 
  hour0 = 2; 
  hour1 = 1; 
  counter = 0; 
} 
void clock(){
	second0++;
  if (second0 > 9) 
  { 
    second0 = 0 ;
		second1++;
    if (second1 > 5) 
    { 
      second1 = 0; 
      minute0++; 
      if (minute0 > 9) 
      { 
        minute0 = 0; 
        minute1++; 
        if (minute1 > 5) 
        {
          minute1 = 0; 
          hour0++; 
          if (hour0 == 4 && hour1 == 2) 
          { 
            hour0 = hour1 = 0; 
            Dater();
          } 
          else if (hour0 > 9) 
          { 
            hour0 = 0; 
            hour1++; 
          } 
        } 
      } 
    } 
  } 
}
void Dater(){ 
  state();          
  date=(date+1)%7; 
	day0++;
  switch(day0) 
  { 
  case 10: 
    { 
      if(day1 == 2 && month0 == 2 && month1 == 0 ) //???,?2?30????3?1?
      {
        day0 = 1; 
        day1 = 0; 
        month0++; 
      } 
      else //?????10?1 
      { 
        day0 = 0; 
        day1++; 
      } 
    } 
    break; 
  case 1: 
    { 
      if(day1 == 3 && small_mon) //??31???????1?,??+1 
      { 
        day0 = 1; 
        day1 = 0; 
        month0++; 
      } 
    } 
    break; 
  case 2: 
    { 
      if(day1 == 3) 
      { 
        day0 = 1; 
        day1 = 0; 
        month0++; 
      } 
    } 
    break; 
  case 9:
    { 
      if(day1 == 2 && !leap_year && month0 == 2 && month1 == 0) //???,?2?29???3?1?
      { 
        day0 = 1; 
        day1 = 0; 
        month0++; 
      } 
    } 
    break; 
  default: 
    break; 
  } 
  switch(month0) 
  { 
  case 10: 
    { 
      month0 = 0; 
      month1++; 
    } 
    break; 
  case 3: 
    { 
      if(month1 == 1) 
      { 
        month0 = 1; 
        month1 = 0; 
        year0++; 
      } 
    } 
    break ; 
  } 
  if(year0 > 9)
  { 
    year0 = 0; 
    year1++; 
    if(year1 > 9) 
    { 
      year1 = 0; 
      year2++; 
      if(year2 > 9) 
      { 
        year2 = 0; 
        year3++; 
        if(year3 > 9) 
          year3 = 0; 
      } 
    } 
  } 
} 
void state(){ 
  switch(month0) 
  { 
  case 1: 
    if(month1 == 1) //??11?,????
      small_mon = 1; 
    else //??1?,?????
    small_mon = 0; 
    break; 
  case 4: 
  case 6: 
  case 9: 
    small_mon = 1;
    break; 
  default: 
    small_mon = 0; 
    break; 
  } 
  if((year3 * 1000 + year2 * 100 + year1 * 10 + year0) % 100 == 0) 
  { 
    if((year3 * 1000 + year2 * 100 + year1 * 10 + year0) % 400 == 0)
			leap_year = 1; 
  }else if((year3 * 1000 + year2 * 100 + year1 * 10 + year0) % 4 == 0) 
    leap_year = 1; 
  else 
    leap_year = 0; 
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
void DISP_Str(char addr1,char *str){
	LCD_CMD(addr1);
	while(*str != 0)
		LCD_DATA(*str++);
}
void DISP_Int(char addr1, int v1){
	LCD_CMD(addr1);
	LCD_DATA(v1+0x30);
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