// buzzer.h
// Header file containing main alarm tune

//define timer scaling value for each note
#define G3 196
#define A3 220
#define As_Bf_3 233
#define B3 247
#define C4 262
#define D4 294
#define Ds_Ef_4 311
#define E4 330
#define F4 349
#define G4 392
//
int i;

void First_Section(){
  #define Notes_Index 32
  unsigned int Song_Notes[Notes_Index]={G4,C4,Ds_Ef_4,F4,G4,C4,Ds_Ef_4,F4,G4,C4,E4,F4,G4,C4,E4,F4,G4,C4,E4,F4,G4,C4,E4,F4,G4,C4,Ds_Ef_4,F4,G4,C4,Ds_Ef_4,F4}; //insert notes of song in array
  unsigned int Notes_Duration[Notes_Index]={4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,12,12,2,2,8,8,2,2}; //relative length of each note
  for (i=0;i<Notes_Index;i++){
                  Sound_Play(Song_Notes[i],80*Notes_Duration[i]);
                  delay_ms(50);
              }
}

void Second_Section(){
  #define Notes_Index 25
  unsigned int Song_Notes[Notes_Index]={D4,G3,As_Bf_3,C4,D4,G3,As_Bf_3,C4,D4,G3,As_Bf_3,C4,D4,G3,As_Bf_3,C4,F4,As_Bf_3,Ds_Ef_4,D4,F4,As_Bf_3,Ds_Ef_4,D4,C4}; //insert notes of song in array
  unsigned int Notes_Duration[Notes_Index]={4,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,12,12,2,2,8,8,2,2,12}; //relative length of each note
  for (i=0;i<Notes_Index;i++){
                  Sound_Play(Song_Notes[i],80*Notes_Duration[i]);
                  delay_ms(50);
              }
}

void buz() {
      Sound_Init(&PORTC,2);
      //while(1){
         First_Section();
         Second_Section();
      delay_ms(1000);
      //}
}