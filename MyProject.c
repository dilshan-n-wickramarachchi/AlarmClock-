//Main program
//Alarm Clock

//Headers
#include "buzzer.h"
#include "cout_buz.h"

// LCD pin Configuration
// Lcd pinout settings
sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

// Pin direction
sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

//Assigning Keypad Port
char keypadPort at PORTB;

//Variable Decleration
// Global Variables to hold Time and Date values
unsigned short secondbin  = 0;
unsigned short minutebin =0;
unsigned short hrbin = 12;
unsigned short ap = 0;
unsigned short monthbin =1;
unsigned short datebin = 1;
unsigned short yearbin = 16;

char time[] = "00:00:00 PM";                                                    //Array Containing complete Time
char date[] = "00-00-2000";                                                     //Array Containing complete Date

                                                                                //Global Variables that are mainly used inside specific methods.
char time_set[] = "00:00 PM";
char date_set[] = "00-00-2000 ";
char timer[]    = "00:00";
char alarm[] = "00:00 PM 0FF"  ;
char alarm2[] = "00:00 PM 0FF"  ;
char temp[] = "00:00:00" ;
char kp = 0;

unsigned char BCD2UpperCh(unsigned char bcd){                                   //This method output the upper BCD value
  return ((bcd >> 4) + '0');
}

unsigned char BCD2LowerCh(unsigned char bcd){                                   //This method output the upper BCD value
  return ((bcd & 0x0F) + '0');
}

int Binary2BCD(int a){                                                          //This method coverts a given binary value(variable a) to a BCD value
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

int BCD2Binary(int a){                                                          //This method coverts a given BCD value(variable a) to a binary value
   int r,t;
   t = a & 0x0F;
   r = t;
   a = 0xF0 & a;
   t = a >> 4;
   t = 0x0F & t;
   r = t*10 + r;
   return r;
}

unsigned char readKeyboard() {                                                  //This method handles keyboard inputs and return relevent character
    unsigned char kp1  = 0;                                // Reset key code variable
    // Wait for key to be pressed and released
    do{
      kp1 = Keypad_Key_Press();          // Store key code in kp variable and Key_Press reads the key from keypad when key gets pressed.
      Delay_ms(400);                     // Since Key_Press does not account for releasing of the key reasonable delay is used to avoid repetetive input
    }while(!kp1);

   // Prepare value for output, transform key to it's ASCII value
    switch (kp1) {
      case  1: kp1 = '1'; break; // 1
      case  2: kp1 = '2'; break; // 2
      case  3: kp1 = '3'; break; // 3
      case  4: kp1 = 'A'; break; // A
      case  5: kp1 = '4'; break; // 4
      case  6: kp1 = '5'; break; // 5
      case  7: kp1 = '6'; break; // 6
      case  8: kp1 = 'B'; break; // B
      case  9: kp1 = '7'; break; // 7
      case 10: kp1 = '8'; break; // 8
      case 11: kp1 = '9'; break; // 9
      case 12: kp1 = 'C'; break; // C
      case 13: kp1 = '*'; break; // *
      case 14: kp1 = '0'; break; // 0
      case 15: kp1 = '#'; break; // #
      case 16: kp1 = 'D'; break; // D
    }
    return kp1;
}

unsigned char setNumber(char *range){                                           //This function is used to iterate till user gives a specific input. Expected inputs are give to the variable range
    kp = 0 ;
    while(1){
      kp = readKeyboard();
      if(strchr(range,kp)){                                                     //Check the presence of give input in the expected inputs
          break;
      }
    }
    return kp  ;
}


void checkAlarm(){                                                              //This method checks the alarm and time of the internal clock
    if(time[0] == alarm[0] & time[1]==alarm[1] & time[3]==alarm[3] & time[4]==alarm[4] & time[9]==alarm[6] & alarm[10]=='N'){
        Lcd_Cmd(_LCD_CLEAR);
        Lcd_out(1,1,time);
        Lcd_out(1,16,'&');

        Lcd_Cmd(_LCD_BLINK_CURSOR_ON);
       	Lcd_out(1,16,"");

        buz();                                                                  // Playing Game Of Thrones to wake you up!
        
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
        }else{                                                                  //This block is used to znoose by 10min
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

void interrupt(){                                                               //Timer Interrupt (configured to 1 second) changes the time array and date array
  if (TMR0IF_bit){
    TMR0IF_bit = 0;
    TMR0H         = 0x0B;                                                       //Configurations
    TMR0L         = 0xDC;
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

void time2Str(int temp){ //Mode 0-for permanent memory. If not given temp memory
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

void setTime(){                                                                 //Writing time in pic
      minutebin = ((time_set[3]-48)*10 + (time_set[4]-48));                     //12:00;00 PM   default
      hrbin = ((time_set[0]-48)*10 + (time_set[1]-48));
      secondbin  = 0;
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

void setDate(){                                                                 //Writing date in pic
      monthbin =((date_set[3]-48)*10 + (date_set[4]-48));                       //01-01-2016  default
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

void setLcd(){                                                                  //GUI for home screen
        Lcd_Cmd(_LCD_CLEAR);
        Lcd_Cmd(_LCD_CURSOR_OFF);
        Lcd_Out(1,1,"Alarm Clock");
        Lcd_Out(2,1,"Group 29...");
        Delay_ms(1000);
        Lcd_Cmd(_LCD_CLEAR);
}

void Counter(){                                                                 //This method carryout Countdown timer
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
     cout_buz();                                                                //sound clip to inform end of countdown
     Delay_ms(500);
     setLcd();
}

void main() {

   Sound_Init(&PORTC,2);                                                        //Initialte buzzer
   Keypad_Init();                                                               // Initialize Keypad
   Lcd_Init();                                                                  // Initialize LCD
   
   Lcd_Cmd(_LCD_CLEAR);                                                         // Clear display
   Lcd_Cmd(_LCD_CURSOR_OFF);                                                    // Cursor off
   
   //Configuring PIC
   CMCON = 0x07;                                                                // To turn off comparators
   ADCON1 = 0x0F;                                                               // To turn off analog to digital converters
   LATD = 0x00;                                                                 //Specific configuration in pic18f to access LCD
   ADCON1 |= 0x06;                                                              // Configure all ports with analog function as digital
   CMCON  |= 7;                                                                 // Disable comparators
   TRISA;     //0x00                                                            // Configure pins for input and output, not used
   TRISB = 0xF0;



   //Timer Settings  configurations
   T0CON         = 0x84;
   TMR0H         = 0x0B;
   TMR0L         = 0xDC;
   GIE_bit       = 1;
   TMR0IE_bit    = 1;
    
   setLcd();                                                                    //Starting the GUI of the clock
    
    while(1){                                                                   //Main loop of the clock
        time2Str(0);
        date2Str();
        Lcd_out(1,1,time);
        Lcd_out(2,1,date);
        
        if (alarm[10]=='N'){                                                    //Checking for turned on alarms
           Lcd_out(2,16,'&');
           checkAlarm();
        }
        
        kp = Keypad_Key_Click();                                                //Listing to button clicks

        if(kp ==12){                                                            // Settings :- Change Time and date.
          Lcd_Cmd(_LCD_CLEAR);                                                  // Note that codings are carried out so that invalid inputs are not ignored such as 12hr format, leap years.
          Lcd_Cmd(_LCD_CURSOR_OFF);                                             // Thereore to proceed user must entre correct values.
          Lcd_Out(1,1,"A. Set Time");                                           //i.e. - User will not be able to input incorrect times, dates
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

        }else if(kp == 'B'){                                                    //Setting date
            
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
      }else if(kp == 8){                                                        //Countdown Timer:-
          Lcd_Cmd(_LCD_CLEAR);                                                  //If previous values are present user can continue previous countdown or starts a new countdown
          Lcd_out(1,1,timer);

          if(timer[0]=='0' & timer[1]=='0' & timer[3]=='0' & timer[4]=='0'){
          	Lcd_out(1,1,timer);
                Lcd_out(2,1,"A. Set");                                          //Starting a new countdown
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
          		Counter();                                              //Using previous countdown values
          	}else if(kp == 'D'){
          		setLcd();
          	}
          }
      }else if(kp==4){                                                          //Setting up an alarm:-
          Lcd_Cmd(_LCD_CLEAR);                                                  //User can set an alarm, edit or check the alarm
          Lcd_Out(1,1,"A.Set Alarm");                                           // '&' us shown in (2,16) cell in LCD display to indicate alarm is activated
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