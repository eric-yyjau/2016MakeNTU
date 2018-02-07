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

  
  pinMode(6, INPUT);    //sonar right
  pinMode(5, OUTPUT);   //sonar right output
  pinMode(4, INPUT);    //sonar left
  pinMode(3, OUTPUT);   //sonar left output
  pinMode(2, OUTPUT);   //Beep 
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
}

bool lightOn = 0;
long t = millis();
//long tSnd = millis();
enum mode{
  reset,
  left,
  right,
  doNothing
};
int state = reset;

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
      digitalWrite(2, LOW);
      lightOn = false;
      break;
    case left:
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(2, HIGH);
      lightOn = true;
      break;
    case right:
      digitalWrite(9, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(2, HIGH);
      lightOn = true;
      break;
    case doNothing:
      break;
  }
    
}
long get_distanceRight() {
  digitalWrite(5, HIGH);
  delayMicroseconds(30);
  digitalWrite(5, LOW);
  
  long duration = pulseIn(6, HIGH, 300000L);

  if (duration == 0) return -1;
  return duration * 343LL * 50 / 1000000;
}
long get_distanceLeft() {
  digitalWrite(3, HIGH);
  delayMicroseconds(30);
  digitalWrite(3, LOW);
  
  long duration = pulseIn(4, HIGH, 300000L);

  if (duration == 0) return -1;
  return duration * 343LL * 50 / 1000000;
}
void shimmer(bool near){
  long beepRate = 500;
  if(near) beepRate = 150;
  long tNow = millis();
  //Serial.println(1);
  if( tNow - t <= beepRate ) return;
  if(state != reset){
    //Serial.println(20);
    if(lightOn) light(reset);
    else light(state);
    t = tNow;
  }
}
/*
void sound(bool near){
  long beepRate = 400;
  long beepFast = 100;
  long tNow = millis();
  if( tNow - tSnd <= 100 ) return;
  if(state != reset){
    Serial.println(20);
    if(lightOn) light(reset);
    else light(state);
    t = tNow;
  }
  if(near){
    if( tNow - tSnd <= beepFast ) return;
    else{
      digitalWrite(2, LOW);
    }
  }
  else{
    
  }
}
*/
void loop() {
  // put your main code here, to run repeatedly:
  bool near = false;
  long distance = 100;
  long distanceIgnore = 15;
  light(judge() );
  Serial.println("DDDDDDDDDDDDDDDDDDDDDD");
  //sound(near);
  if(!reset){
    near = false;
    long distanceRight = get_distanceRight();
    long distanceLeft =  get_distanceLeft();
    //Serial.println(distanceRight);
    //Serial.println(distanceLeft);
    if( distanceLeft < distance && distanceLeft > distanceIgnore){
      if(state == left){
        near = true;
        Serial.println("left fuck");
      }
    }
    else if( distanceRight < distance && distanceRight > distanceIgnore){
      if(state == right){
        near = true;
        Serial.println("right fuck");
      }
    }
  }
  shimmer(near);
}
