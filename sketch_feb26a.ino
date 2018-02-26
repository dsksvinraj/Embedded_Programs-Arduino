#define go1 0
#define wait1 1
#define go2 2
#define wait2 3
#define go3 4
#define wait3 5
#define go4 6
#define wait4 7

struct state {
  unsigned long out[2];
  unsigned long wait;
  unsigned long next[16];
};
typedef const struct state STyp;

unsigned long S;
unsigned long input,previous_input;
unsigned long i;

STyp FSM[8]={
  {{0x32,0x02},3000000,{go1,wait1,wait1,wait1,wait1,wait1,wait1,wait1,go1,wait1,wait1,wait1,wait1,wait1,wait1,wait1}},
  {{0x52,0x02},500000,{go2,go4,go3,go3,go2,go2,go2,go2,go2,go4,go3,go3,go2,go2,go2,go2}},
  {{0x86,0x02},3000000,{go2,wait2,wait2,wait2,go2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2,wait2}},
  {{0x8A,0x02},500000,{go3,go4,go3,go4,go3,go4,go3,go3,go1,go1,go3,go3,go1,go4,go3,go3}},
  {{0x90,0x03},3000000,{go3,wait3,go3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3,wait3}},
  {{0x91,0x02},500000,{go4,go4,go3,go4,go2,go4,go2,go4,go1,go4,go1,go4,go1,go4,go1,go4}},
  {{0x92,0x08},3000000,{go4,go4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4,wait4}},
  {{0x92,0x04},500000,{go1,go4,go3,go3,go2,go2,go2,go2,go1,go1,go1,go1,go1,go1,go1,go1}}
};
int main() {
  DDRD = 0B11111111; //set port D as output
  DDRB = 0B00001111; //set port B pins [3,2,1,0] as output
  DDRC = 0B00000000; //set port C pins [3,2,1,0] as input
  S = go1; //set the initial state of the machine

 while(1){
  PORTD = FSM[S].out[0]; //outputs to led
  PORTB = FSM[S].out[1]; //outputs to led
  for(i=0;i<FSM[S].wait;i++){
    previous_input = input;
    input = PINC;
    if(input!=previous_input)
    break;
  }
  input = PINC;
  S = FSM[S].next[input];
  
}
return 0;
}

