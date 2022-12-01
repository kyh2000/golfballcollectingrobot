#define ENABLE_A  3  
#define IN1_A  2   
#define IN2_A  4   
#define ENABLE_B  9  
#define IN3_B  7   
#define IN4_B  8
#define ENABLE_C  11
#define IN5_C  13
#define IN6_C  12   
#define buzzerPin  6


char cmd;
byte speedDC = 255;   
int tones = 370;
int endtones = 494;
int Rg= 200; //right wheel normal speed
int Lg=210; //left wheel normal speed
int Rt=100; //right wheel turn speed
int Lt=110;
#define IN5_C  13
#define IN6_C  12    
void setup() {
  pinMode(ENABLE_A,OUTPUT);  
  pinMode(IN1_A,OUTPUT);  
  pinMode(IN2_A,OUTPUT);  
  pinMode(ENABLE_B,OUTPUT);  
  pinMode(IN3_B,OUTPUT);  
  pinMode(IN4_B,OUTPUT);
  pinMode(ENABLE_C,OUTPUT);  
  pinMode(IN5_C,OUTPUT);  
  pinMode(IN6_C,OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}
void motor_speedL(int spd)  
{  
  analogWrite(ENABLE_A,spd);   
}
void motor_speedR(int spd)  
{    
  analogWrite(ENABLE_B,spd);  
}
void motor_speed(int spd) 
{
  analogWrite(ENABLE_A,spd);
  analogWrite(ENABLE_B,spd);
}

void spin_speed(int spd)
{
  analogWrite(ENABLE_C,spd);
}
void ballspin() //ball cleaning
{
  digitalWrite(IN5_C,LOW);  
  digitalWrite(IN6_C,HIGH);
  spin_speed(110);
}
void gofoward() //fix go foward
{
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(177.5);
  digitalWrite(IN3_B,HIGH);  
  digitalWrite(IN4_B,LOW);
  motor_speedR(150);
  delay(1);
}

void start() //start duration
{
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(200);
  digitalWrite(IN3_B,HIGH);  
  digitalWrite(IN4_B,LOW);
  motor_speedR(200);
  delay(2000);
}

void left() //turn left
{
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(0);
  digitalWrite(IN3_B,HIGH);  
  digitalWrite(IN4_B,LOW);
  motor_speedR(240);
  delay(10000);
  
  
  motor_speed(0);
  delay(2000);
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(100);
  delay(500);
  start();
}
void right() //turn right
{
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(255);
  digitalWrite(IN3_B,HIGH);  
  digitalWrite(IN4_B,LOW);
  motor_speedR(0);
  delay(10000);
  motor_speed(0);
  delay(2000);
  digitalWrite(IN3_B,HIGH);  
  digitalWrite(IN4_B,LOW);
  motor_speedR(100);
  delay(500);
  start();
  
}
void rightU() //right Uturn
{
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(Lg);
  digitalWrite(IN3_B,LOW);  
  digitalWrite(IN4_B,HIGH);
  motor_speedR(Rt);
  delay(5300);
  motor_speed(0);
  delay(1000);
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(0);
  digitalWrite(IN3_B,HIGH);  
  digitalWrite(IN4_B,LOW);
  motor_speedR(200);
  delay(300);
  motor_speed(0);
  delay(1000);
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(150);
  digitalWrite(IN3_B,HIGH);  
  digitalWrite(IN4_B,LOW);
  motor_speedR(130);
  delay(1000);
}
void finish() //finish
{
  digitalWrite(IN1_A,LOW);  
  digitalWrite(IN2_A,LOW);
  motor_speedR(0);
  digitalWrite(IN3_B,LOW);  
  digitalWrite(IN4_B,LOW);
  motor_speedL(0);
  digitalWrite(IN3_B,LOW);  
  digitalWrite(IN4_B,LOW);
  motor_speedL(0);
  for (int i = 0; i<3; i++)
  {
     tone(buzzerPin, endtones);
     delay(1000); 
     noTone(buzzerPin);
     delay(500);
     tone(buzzerPin, endtones);
     delay(1000);
     noTone(buzzerPin);
     delay(1000);
  }
   delay(1000000000);
}
void sound() //sound function
{
  digitalWrite(IN1_A,LOW);  
  digitalWrite(IN2_A,LOW);
  motor_speedR(0);
  digitalWrite(IN3_B,LOW);  
  digitalWrite(IN4_B,LOW);
  motor_speedL(0);
 
  tone(buzzerPin, tones);
  delay(5000); 
  
  noTone(buzzerPin);
}

void leftU() ///left Uturn
{
  digitalWrite(IN1_A,HIGH);  
  digitalWrite(IN2_A,LOW);
  motor_speedL(210);
  digitalWrite(IN3_B,LOW);  
  digitalWrite(IN4_B,HIGH);
  motor_speedR(150);
  //delay(3000);
  delay(5000);
  
}



void loop() {
  
 
  if(Serial.available()){
    cmd = Serial.read(); 
    ballspin();
    //start();
    if(cmd=='a'){
      left();
      delay(100);
    }
    else if(cmd=='g'){
      gofoward();
      delay(100);
    }
    else if(cmd=='d'){
      right();
      delay(100);
    }
    else if(cmd=='r'){
      rightU();
      delay(100);
    }
    else if(cmd=='l'){
      leftU();
      delay(100);
    }
    else if(cmd=='s'){
      sound();
      delay(100);
    }
    else if(cmd=='f'){
      finish();
      delay(100);
    }
    else if(cmd=='t'){
      start();
      delay(100);
    }
  }
}
  
  
 
