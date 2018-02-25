#define go1 0
#define wait1 1
#define go2 2
#define wait2 3
#define go3 4
#define wait3 5
#define go4 6
#define wait4 7


void DELAY(unsigned long ms);
struct state {
  unsigned long out[2];
  unsigned long wait;
  unsigned long next[16];
};
typedef const struct state STyp;

unsigned long S;
unsigned long input;
unsigned long i;

STyp FSM[8]={
  {{0x32,0x02},3000,{go1,wait1,wait1,wait1,wait1,wait1,wait1,wait1,go1,wait1,wait1,wait1,wait1,wait1,wait1,wait1}},
  {{0x52,0x02},500,{go2,go4,go3,go3,go2,go2,go2,go2,go2,go4,go3,go3,go2,go2,go2,go2}},
  {{0x86,0x02},3000,{go2,wait2,wait2,wait2,go2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2}},
  {{0x8A,0x02},500,{go3,go4,go3,go4,go3,go4,go3,go3,go1,go1,go3,go3,go1,go4,go3,go3}},
  {{0x90,0x03},3000,{go3,wait3,go3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3}},
  {{0x91,0x02},500,{go4,go4,go3,go4,go2,go4,go2,go4,go1,go4,go1,go4,go1,go4,go1,go4}},
  {{0x92,0x08},3000,{go4,go4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4}},
  {{0x92,0x04},500,{go1,go4,go3,go3,go2,go2,go2,go2,go1,go1,go1,go1,go1,go1,go1,go1}}
};
int main() {
  DDRD = 0B11111111;
  DDRB = 0B00001111;
  DDRC = 0B00000000;
  S = go1;
  
 while(1){
  PORTD = FSM[S].out[0];
  PORTB = FSM[S].out[1];
  DELAY(FSM[S].wait);
  input = PINC;
  S = FSM[S].next[input];
  
}
return 0;
}
void DELAY(unsigned long ms)
{
  int c=ms;
  i=16000000;
     while(c>0){
      c--;
    }
  while(i>0){
    i--;
  }
}

