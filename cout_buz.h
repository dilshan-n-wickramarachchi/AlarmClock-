//cout_buz.h
//Header file containing beep sound for countdown timer

//define timer scaling value for each note
#define C3 130.813
#define D3 146.832
#define E3 164.814
#define F3 174.614
#define G3 195.998
#define A3 220.000
#define B3 246.942
#define C4 261.626
#define D4 293.665
#define Ds_Ef_4 311.127
#define E4 329.628
#define F4 349.228
#define G4 391.995
#define A4 440.000
#define B4 493.883
#define N 0
#define Notes_Index 14

void cout_buz() {
          
      int i;
      int Song_Notes[Notes_Index]={N}; //insert notes of song in array
      int Notes_Duration[Notes_Index]={8}; //relative length of each note
      
      for ( i=0;i<Notes_Index;i++){
          Sound_Play(Song_Notes[i],80*Notes_Duration[i]);
          delay_ms(50);
      }
}