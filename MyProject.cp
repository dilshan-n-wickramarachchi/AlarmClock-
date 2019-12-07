#line 1 "C:/Users/Dilshan N. Wick/Desktop/New folder (2)/MyProject.c"
#line 1 "c:/users/dilshan n. wick/desktop/new folder (2)/buzzer.h"
#line 16 "c:/users/dilshan n. wick/desktop/new folder (2)/buzzer.h"
int i;

void First_Section(){

 unsigned int Song_Notes[ 32 ]={ 392 , 262 , 311 , 349 , 392 , 262 , 311 , 349 , 392 , 262 , 330 , 349 , 392 , 262 , 330 , 349 , 392 , 262 , 330 , 349 , 392 , 262 , 330 , 349 , 392 , 262 , 311 , 349 , 392 , 262 , 311 , 349 };
 unsigned int Notes_Duration[ 32 ]={4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,12,12,2,2,8,8,2,2};
 for (i=0;i< 32 ;i++){
 Sound_Play(Song_Notes[i],80*Notes_Duration[i]);
 delay_ms(50);
 }
}

void Second_Section(){

 unsigned int Song_Notes[ 25 ]={ 294 , 196 , 233 , 262 , 294 , 196 , 233 , 262 , 294 , 196 , 233 , 262 , 294 , 196 , 233 , 262 , 349 , 233 , 311 , 294 , 349 , 233 , 311 , 294 , 262 };
 unsigned int Notes_Duration[ 25 ]={4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,12,12,2,2,8,8,2,2,12};
 for (i=0;i< 25 ;i++){
 Sound_Play(Song_Notes[i],80*Notes_Duration[i]);
 delay_ms(50);
 }
}

void buz() {
 Sound_Init(&PORTC,2);

 First_Section();
 Second_Section();
 delay_ms(1000);

}
#line 1 "c:/users/dilshan n. wick/desktop/new folder (2)/cout_buz.h"
#line 23 "c:/users/dilshan n. wick/desktop/new folder (2)/cout_buz.h"
void cout_buz() {

 int i;
 int Song_Notes[ 14 ]={ 0 };
 int Notes_Duration[ 14 ]={8};

 for ( i=0;i< 14 ;i++){
 Sound_Play(Song_Notes[i],80*Notes_Duration[i]);
 delay_ms(50);
 }
}
#line 10 "C:/Users/Dilshan N. Wick/Desktop/New folder (2)/MyProject.c"
sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;


sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


char keypadPort at PORTB;



unsigned short secondbin = 0;
unsigned short minutebin =0;
unsigned short hrbin = 12;
unsigned short ap = 0;
unsigned short monthbin =1;
unsigned short datebin = 1;
unsigned short yearbin = 16;

char time[] = "00:00:00 PM";
char date[] = "00-00-2000";


char time_set[] = "00:00 PM";
char date_set[] = "00-00-2000 ";
char timer[] = "00:00";
char alarm[] = "00:00 PM 0FF" ;
char alarm2[] = "00:00 PM 0FF" ;
char temp[] = "00:00:00" ;
char kp = 0;

unsigned char BCD2UpperCh(unsigned char bcd){
 return ((bcd >> 4) + '0');
}

unsigned char BCD2LowerCh(unsigned char bcd){
 return ((bcd & 0x0F) + '0');
}

int Binary2BCD(int a){
 int t1, t2;
 t1 = a%10;
 t1 = t1 & 0x0F;
 a = a/10;
 t2 = a%10;
 t2 = 0x0F & t2;
 t2 = t2 << 4;
 t2 = 0xF0 & t2;
 t1 = t1 | t2;
 return t1;
}

int BCD2Binary(int a){
 int r,t;
 t = a & 0x0F;
 r = t;
 a = 0xF0 & a;
 t = a >> 4;
 t = 0x0F & t;
 r = t*10 + r;
 return r;
}

unsigned char readKeyboard() {
 unsigned char kp1 = 0;

 do{
 kp1 = Keypad_Key_Press();
 Delay_ms(400);
 }while(!kp1);


 switch (kp1) {
 case 1: kp1 = '1'; break;
 case 2: kp1 = '2'; break;
 case 3: kp1 = '3'; break;
 case 4: kp1 = 'A'; break;
 case 5: kp1 = '4'; break;
 case 6: kp1 = '5'; break;
 case 7: kp1 = '6'; break;
 case 8: kp1 = 'B'; break;
 case 9: kp1 = '7'; break;
 case 10: kp1 = '8'; break;
 case 11: kp1 = '9'; break;
 case 12: kp1 = 'C'; break;
 case 13: kp1 = '*'; break;
 case 14: kp1 = '0'; break;
 case 15: kp1 = '#'; break;
 case 16: kp1 = 'D'; break;
 }
 return kp1;
}

unsigned char setNumber(char *range){
 kp = 0 ;
 while(1){
 kp = readKeyboard();
 if(strchr(range,kp)){
 break;
 }
 }
 return kp ;
}


void checkAlarm(){
 if(time[0] == alarm[0] & time[1]==alarm[1] & time[3]==alarm[3] & time[4]==alarm[4] & time[9]==alarm[6] & alarm[10]=='N'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,time);
 Lcd_out(1,16,'&');

 Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
 Lcd_out(1,16,"");

 buz();

 Lcd_out(2,1,"A.Stop");
 Lcd_out(2,9,"B.Snooze");

 kp = setNumber("AB");
 Lcd_cmd(_LCD_CURSOR_OFF);

 if (kp=='A'){
 alarm[10] = 'F';
 alarm[11] = 'F' ;
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Alarm Stopped");
 Lcd_out(2,1,".....");
 Delay_ms(1000);
 }else{
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,"Snooze 10min");
 if(alarm[3]<'5'){
 alarm[3] += 1;
 }else if(alarm[1]=='2' & alarm[0] =='1' & alarm[6]=='A'){
 alarm[1]='0';
 alarm[0] = '1';
 alarm[6]='P';
 }else{
 alarm[3] = '0';
 alarm[1] += 1 ;
 }
 Lcd_out(2,1,alarm);
 Delay_ms(1000);
 Lcd_Cmd(_LCD_CLEAR);
 }

 }
}

void interrupt(){
 if (TMR0IF_bit){
 TMR0IF_bit = 0;
 TMR0H = 0x0B;
 TMR0L = 0xDC;
 secondbin++;

 if(secondbin >= 60){
 secondbin = 0;
 minutebin++;
 }
 if (minutebin >= 60){
 hrbin++;
 minutebin = 0;
 }
 if (hrbin > 12){
 hrbin = 1;
 minutebin = 0;
 }
 if (hrbin ==12 && minutebin == 0 && secondbin == 0) ap = !ap;
 }
}

void time2Str(int temp){
 time[0] = BCD2UpperCh(Binary2BCD(hrbin));
 time[1] = BCD2LowerCh(Binary2BCD(hrbin));
 time[3] = BCD2UpperCh(Binary2BCD(minutebin));
 time[4] = BCD2LowerCh(Binary2BCD(minutebin));
 time[6] = BCD2UpperCh(Binary2BCD(secondbin));
 time[7] = BCD2LowerCh(Binary2BCD(secondbin));

 if(ap){
 time[9] = 'P';
 time[10] = 'M';
 }
 else{
 time[9] = 'A';
 time[10] = 'M';
 }

}

void date2Str(){
 date[0] = BCD2UpperCh(Binary2BCD(datebin));
 date[1] = BCD2LowerCh(Binary2BCD(datebin));
 date[3] = BCD2UpperCh(Binary2BCD(monthbin));
 date[4] = BCD2LowerCh(Binary2BCD(monthbin));
 date[8] = BCD2UpperCh(Binary2BCD(yearbin));
 date[9] = BCD2LowerCh(Binary2BCD(yearbin));
}

void setTime(){
 minutebin = ((time_set[3]-48)*10 + (time_set[4]-48));
 hrbin = ((time_set[0]-48)*10 + (time_set[1]-48));
 secondbin = 0;
 if(time_set[6]== 'P'){ap = 1;}else{ap = 0;}
 time2Str(0);
 date2Str();
 Lcd_out(1,1,time);
 Lcd_out(2,1,date);

 if (alarm[10]=='N'){
 Lcd_out(2,16,'&');
 checkAlarm();
 }
 Delay_ms(100);
}

void setDate(){
 monthbin =((date_set[3]-48)*10 + (date_set[4]-48));
 datebin = ((date_set[0]-48)*10 + (date_set[1]-48));
 yearbin = ((date_set[8]-48)*10 + (date_set[9]-48));
 time2Str(0);
 date2Str();
 Lcd_out(1,1,time);
 Lcd_out(2,1,date);

 if (alarm[10]=='N'){
 Lcd_out(2,16,'&');
 checkAlarm();
 }
 Delay_ms(100);
}

void setLcd(){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"Alarm Clock");
 Lcd_Out(2,1,"Group 29...");
 Delay_ms(1000);
 Lcd_Cmd(_LCD_CLEAR);
}

void Counter(){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(2,1,"mm:ss");

 while(1){
 while(1){
 while(1){
 while(1){
 Lcd_Out(1,1,timer);
 Delay_ms(1000);
 if(timer[4]=='0'){ break;}
 timer[4] = timer[4]-1;
 }
 if(timer[3]=='0'){
 break;
 }else{
 timer[3] = timer[3]-1;
 timer[4] = '9';
 }
 }
 if(timer[1]== '0'){
 break;
 }else{
 timer[1] = timer[1] - 1 ;
 timer[3] = '5';
 timer[4] = '9';
 }
 }
 if(timer[0]== '0'){
 break;
 }else{
 timer[0] = timer[0] - 1 ;
 timer[1] = '9';
 timer[3] = '5';
 timer[4] = '9';
 }

 }
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,timer);
 Lcd_out(1,1,"Time is over!");
 cout_buz();
 Delay_ms(500);
 setLcd();
}

void main() {

 Sound_Init(&PORTC,2);
 Keypad_Init();
 Lcd_Init();

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);


 CMCON = 0x07;
 ADCON1 = 0x0F;
 LATD = 0x00;
 ADCON1 |= 0x06;
 CMCON |= 7;
 TRISA;
 TRISB = 0xF0;




 T0CON = 0x84;
 TMR0H = 0x0B;
 TMR0L = 0xDC;
 GIE_bit = 1;
 TMR0IE_bit = 1;

 setLcd();

 while(1){
 time2Str(0);
 date2Str();
 Lcd_out(1,1,time);
 Lcd_out(2,1,date);

 if (alarm[10]=='N'){
 Lcd_out(2,16,'&');
 checkAlarm();
 }

 kp = Keypad_Key_Click();

 if(kp ==12){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"A. Set Time");
 Lcd_Out(2,1,"B. Set Date");

 kp = setNumber("ABD");

 if(kp == 'A'){
 *time_set = "00:00 PM";
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,time_set);
 Lcd_out(2,1,"Set Hour");
 Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
 Lcd_out(1,1,"");
 time_set[0] = setNumber("01");
 Lcd_out(1,1,time_set);
 Lcd_out(1,2,"");
 if(time_set[0]=='1'){time_set[1] = setNumber("012");}else{time_set[1] = setNumber("0123456789");}
 Lcd_out(1,1,time_set);
 Lcd_out(2,1,"Set Minutes");
 Lcd_out(1,4,"");
 time_set[3] = setNumber("012345");
 Lcd_out(1,1,time_set);
 Lcd_out(1,5,"");
 time_set[4] = setNumber("0123456789");
 Lcd_out(1,1,time_set);
 Lcd_out(1,7,"");
 if (time_set[0]=='1' & time_set[1]=='2' ){Lcd_out(2,1,"A-AM        B-PM");time_set[6]=setNumber("AB"); if(time_set[6]=='A'){time_set[6]=='A';}else{time_set[6]='P';}}
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_cmd(_LCD_CURSOR_OFF);

 Lcd_out(1,1,time_set);
 Lcd_out(2,1,"A.Save");
 Lcd_out(2,11,"D.Exit");

 kp = setNumber("AD");

 if(kp == 'A'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"Saving Time");
 Lcd_Out(2,1,"......");
 Delay_ms(500);
 Lcd_Cmd(_LCD_CLEAR);
 setTime();
 }else{
 setLcd();
 }

 }else if(kp == 'B'){

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,date_set);
 Lcd_out(2,1,"dd:mm:yyyy");
 Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
 Lcd_out(1,9,"");
 date_set[8] = setNumber("0123456789");
 Lcd_out(1,1,date_set);
 Lcd_out(1,10,"");
 date_set[9] = setNumber("0123456789");
 Lcd_out(1,1,date_set);
 Lcd_out(1,4,"");
 date_set[3] = setNumber("01");
 Lcd_out(1,1,date_set);
 Lcd_out(1,5,"");
 if(date_set[3]=='0'){
 date_set[4] = setNumber("123456789");
 Lcd_out(1,1,date_set);
 Lcd_out(1,1,"");
 }else if(date_set[4]=='1'){
 date_set[4] = setNumber("012");
 Lcd_out(1,1,date_set);
 Lcd_out(1,1,"");
 }
 Lcd_out(1,1,date_set);
 Lcd_out(1,1,"");
 if(strchr("469",date_set[4])){
 date_set[0]=setNumber("0123");
 Lcd_out(1,1,date_set);
 Lcd_out(1,2,"");
 if(date_set[0]=='3'){
 date_set[1]=setNumber("01");
 Lcd_out(1,1,date_set);
 }else{
 date_set[1]=setNumber("0123456789");
 Lcd_out(1,1,"");Lcd_out(1,1,date_set);
 }
 }else if(date_set[3]=='1' & date_set[4]=='1'){
 date_set[0]=setNumber("0123");
 Lcd_out(1,1,date_set);
 Lcd_out(1,2,"");
 if(date_set[0]=='3'){
 date_set[1]=setNumber("01");
 Lcd_out(1,1,date_set);
 Lcd_out(1,2,"");
 }else{
 date_set[1]=setNumber("0123456789");
 Lcd_out(1,1,date_set);
 Lcd_out(1,2,"");
 }
 }else if(date_set[3]=='0' & date_set[4]=='2'){
 date_set[0]=setNumber("012");
 Lcd_out(1,1,date_set);
 Lcd_out(1,2,"");
 if(date_set[0]=='2'){
 if(((date_set[8]-48)*10+(date_set[9]))%4 == 0){
 date_set[1] = setNumber("0123456789");
 Lcd_out(1,1,date_set);
 Delay_ms(200);
 }else{
 date_set[1] = setNumber("0123456789");
 Lcd_out(1,1,date_set);
 Delay_ms(200);
 }
 }else{
 date_set[1] = setNumber("0123456789");
 Lcd_out(1,1,date_set);
 }
 }else{
 date_set[0]=setNumber("0123");
 Lcd_out(1,1,date_set);
 Lcd_out(1,2,"");
 if(date_set[0]=='3'){
 Lcd_out(1,2,"");
 date_set[1]='0';
 Lcd_out(1,1,date_set);
 Delay_ms(200);
 }else{
 Lcd_out(1,2,"");
 date_set[1]=setNumber("0123456789");
 Lcd_out(1,1,date_set);
 }
 }
 Delay_ms(200);
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_cmd(_LCD_CURSOR_OFF);
 Lcd_out(1,1,date_set);
 Lcd_out(2,1,"A.Save");
 Lcd_out(2,11,"D.Exit");

 kp = setNumber("AD");

 if(kp == 'A'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"Saving Date");
 Lcd_Out(2,1,"......");
 Delay_ms(500);
 Lcd_Cmd(_LCD_CLEAR);
 setDate();
 }else{
 setLcd();
 }
 }else if(kp=='D'){
 setLcd();
 }
 }else if(kp == 8){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,timer);

 if(timer[0]=='0' & timer[1]=='0' & timer[3]=='0' & timer[4]=='0'){
 Lcd_out(1,1,timer);
 Lcd_out(2,1,"A. Set");
 kp = setNumber("AD");
 if (kp == 'A'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,timer);
 Lcd_out(2,1,"mm:ss");
 Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
 Lcd_out(1,1,"");Delay_ms(200);
 timer[0] = setNumber("012345");
 Lcd_out(1,1,timer);
 Lcd_out(1,2,"");Delay_ms(200);
 timer[1] = setNumber("0123456789");
 Lcd_out(1,1,timer);
 Lcd_out(1,4,"");Delay_ms(200);
 timer[3] = setNumber("012345");
 Lcd_out(1,1,timer);
 Lcd_out(1,5,"");Delay_ms(200);
 timer[4] = setNumber("0123456789");
 Lcd_out(1,1,timer);
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_cmd(_LCD_CURSOR_OFF);
 Lcd_out(1,1,timer);
 Lcd_out(2,1,"A. Start");
 Lcd_out(2,9,"D. Exit");

 kp = setNumber("AD");
 if(kp == 'A'){
 Counter();
 }else {
 setLcd();
 }
 }else{
 setLcd();
 }

 }else{
 Lcd_out(2,1,"A-Reset");
 Lcd_out(2,9,"B-Start");

 kp = setNumber("ABD");
 if (kp == 'A'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,timer);
 Lcd_out(2,1,"mm:ss");
 Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
 Lcd_out(1,1,"");Delay_ms(200);
 timer[0] = setNumber("0123456789");
 Lcd_out(1,1,timer);
 Lcd_out(1,2,"");Delay_ms(200);
 timer[1] = setNumber("0123456789");
 Lcd_out(1,1,timer);
 Lcd_out(1,4,"");Delay_ms(200);
 timer[3] = setNumber("012345");
 Lcd_out(1,1,timer);
 Lcd_out(1,5,"");Delay_ms(200);
 timer[4] = setNumber("0123456789");
 Lcd_out(1,1,timer);
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_cmd(_LCD_CURSOR_OFF);
 Lcd_out(1,1,timer);
 Lcd_out(2,1,"A.Start  D.Exit");

 kp = setNumber("AD");
 if(kp == 'A'){
 Counter();
 }else {
 setLcd();
 }
 }else if(kp == 'B'){
 Counter();
 }else if(kp == 'D'){
 setLcd();
 }
 }
 }else if(kp==4){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Out(1,1,"A.Set Alarm");
 Lcd_Out(2,1,"B.Check Alarm");

 kp = setNumber("ABD");
 if(kp == 'A'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,alarm);
 Lcd_out(2,1,"Set Hour");
 Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
 Lcd_out(1,1,"");
 alarm[0] = setNumber("01");
 Lcd_out(1,1,alarm);
 Lcd_out(1,2,"");
 if(alarm[0]=='1'){alarm[1] = setNumber("012");}else{alarm[1] = setNumber("0123456789");}
 Lcd_out(1,1,alarm);
 Lcd_out(2,1,"Set Minutes");
 Lcd_out(1,4,"");
 alarm[3] = setNumber("012345");
 Lcd_out(1,1,alarm);
 Lcd_out(1,5,"");
 alarm[4] = setNumber("0123456789");
 Lcd_out(1,1,alarm);
 Lcd_out(1,7,"");
 if (alarm[0]=='1' & alarm[1]=='2' ){Lcd_out(2,1,"A-AM        B-PM");alarm[6]=setNumber("AB"); if(alarm[6]=='A'){alarm[6]=='A';}else{alarm[6]='P';}}
 Lcd_out(1,1,alarm);
 Lcd_out(2,1,"A-ON       B-OFF");
 Lcd_out(1,11,"");
 if(setNumber("AB")=='B'){alarm[10] = 'F';alarm[11] = 'F';}else if(setNumber("AB")=='A') {alarm[10] = 'N';alarm[11] = ' ';}
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_cmd(_LCD_CURSOR_OFF);
 Lcd_out(1,1,alarm);
 Lcd_out(2,1,"A.Save  D.Exit ");

 kp = setNumber("AD");

 if(kp == 'A'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,alarm);
 Lcd_out(2,1,"Saving...");
 Delay_ms(1000);
 setLcd();
 }else if(kp == 'D'){
 alarm[10] = 'F';
 alarm[11] = 'F';

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,alarm);
 Lcd_out(2,1,"Cancelling...");
 Delay_ms(1000);
 setLcd();
 }


 }else if(kp=='B'){
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_out(1,1,alarm);
 Lcd_out(2,1,"D. Exit");
 kp = setNumber("D");
 setLcd();

 }else{
 setLcd();
 }
 }
 }
}
