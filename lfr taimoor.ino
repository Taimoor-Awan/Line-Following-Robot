
#include <PID_v1.h>
int S_A = 6;  //speed motor a
int M_A1 = 8;  //motor a = +
int M_A2 = 7;  //motor a = -
int M_B1 = 9;  //motor b = -
int M_B2 = 10;  //motor b = +
int S_B = 11;   //speed motor b

int s1 = 4;  //2nd senor used for the detection of a black line
int s2 = 2;  //3rd senor used for the detection of a black line
int s3 = 3;  //4th senor used for the detection of a black line
int s4 = 5;  //This is right most sensor used for the detection of a check point
int s5 = 12; //This is left most sensor used for the detection of a check point

unsigned long prevt, currt;

int led = 13;
int dspeed=180;
//Define Variables we'll be connecting to
double Setpoint=0;
double Output;
double Deviation;
double Kp=25,Ki = 0,Kd = 2.5;
//Specify the links and initial tuning parameters
PID myPID(&Deviation, &Output, &Setpoint,Kp,Ki,Kd, DIRECT);

void setup()
{
  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  pinMode(S_B, OUTPUT);
  pinMode(S_A, OUTPUT);

  pinMode(led, OUTPUT);

  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);

  delay(200);

  prevt = millis();
  //initialize the variables we're linked to
  Deviation= digitalRead(0);  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  prevt = millis();
}

void loop()
{

  currt = millis();
if(currt-prevt>100)
{
  double lms=dspeed-Output;
  double rms=dspeed+Output;
  prevt = currt;
  Deviation = getDeviation();
  myPID.Compute();
  analogWrite(rms,M_A1);
  analogWrite(lms,M_B1);


}
if((digitalRead(s1)==LOW)&&(digitalRead(s2)==HIGH)&&(digitalRead(s3)==LOW))
{
  forword();
  if((digitalRead(s4)==HIGH)&&(digitalRead(s5)==HIGH))
{
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
}
else if ((digitalRead(s3) == HIGH)&&(digitalRead(s2) == HIGH)&&(digitalRead(s1) == HIGH))
{
  SturnLeft();
  if((digitalRead(s4)==HIGH)&&(digitalRead(s5)==HIGH))
{
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
}
  }
}
else if((digitalRead(s1)==HIGH)&&(digitalRead(s2)==HIGH)&&(digitalRead(s3)==HIGH))
{
  forword();
  if((digitalRead(s4)==HIGH)&&(digitalRead(s5)==HIGH))
{
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
}
}
else if ((digitalRead(s2) ==HIGH)&&(digitalRead(s3) == HIGH)&&(digitalRead(s4) == HIGH))
{
  SturnRight();
  if((digitalRead(s4)==HIGH)&&(digitalRead(s5)==HIGH))
{
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
}
}

else if((digitalRead(s1)==HIGH)&&(digitalRead(s2)==LOW)&&(digitalRead(s3)==LOW))
{
  turnRight();
  if((digitalRead(s4)==HIGH)&&(digitalRead(s5)==HIGH))
{
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
}

}

else if((digitalRead(s1)==LOW)&&(digitalRead(s2)==LOW)&&(digitalRead(s3)==HIGH))
{
  turnLeft();
  if((digitalRead(s4)==HIGH)&&(digitalRead(s5)==HIGH))
{
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
}
}

}


void forword()
{
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
analogWrite(S_A, 2); 
analogWrite(S_B, 240); 
}


void turnRight()
{
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
analogWrite(S_A, 190); 
analogWrite(S_B, 190); 
}

void turnLeft()
{
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);
analogWrite(S_A, 190); 
analogWrite(S_B, 190); 
}
void SturnLeft()
{
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH);
analogWrite(S_A, 190); 
analogWrite(S_B, 190); 
}
void SturnRight()
{
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW); 
analogWrite(S_A, 190); 
analogWrite(S_B, 190); 
} 

double getDeviation()
{
  int sen1=digitalRead(s1);
  int sen2=digitalRead(s2);
  int sen3=digitalRead(s3);
  double dev = (double) ((digitalRead(s1)*(-2.0)) + (digitalRead(s2)*(1.0)) + (digitalRead(s3)*(2.0))/(sen1+sen2+sen3));

  return(dev);
}