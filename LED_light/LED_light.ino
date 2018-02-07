//#include "Timer.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(12, INPUT);    //left
  pinMode(11, INPUT);   //middle
  pinMode(10, INPUT);   //right
  pinMode(9, OUTPUT);    //LED <
  pinMode(8, OUTPUT);   //LED ===
  pinMode(7, OUTPUT);   //LED >
  Serial.begin(9600);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
}

int state = 0;
bool lightOn = 0;
long t = millis();

enum mode{
  reset,
  left,
  right,
  doNothing
};

int judge(){
  if(digitalRead(11) == HIGH){
    state = reset;
    return state; 
  }
  else if(digitalRead(12) == HIGH){
    state = left;
    return state;
  }
  else if(digitalRead(10) == HIGH){
    state = right;
    return state;
  }
  else{
    return doNothing;
  }
}
void light(int mode){
  switch(mode){
    case reset:
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      lightOn = false;
      break;
    case left:
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      lightOn = true;
      break;
    case right:
      digitalWrite(9, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      lightOn = true;
      break;
    case doNothing:
      break;
  }
    
}

void shimmer(){
  long tNow = millis();
  //Serial.println(1);
  Serial.println(tNow-t);
  Serial.println(state);
  if( tNow - t <= 100 ) return;
  if(state != reset){
    Serial.println(20);
    if(lightOn) light(reset);
    else light(state);
    t = tNow;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  light(judge() );
  shimmer();
}
