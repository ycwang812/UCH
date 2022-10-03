///////////////////////////////////////////////
// 程式說明: Motoduino U1馬達測試
// 作者: Dennis Chen 2013
// Email: sinocgtchen@gmail.com
/////////////////////////////////////////////

// 馬達與motoduino的腳位對應
const int Motor_E1 = 5;  // 控制馬達1轉速 digital pin 5 of Arduino (PWM)  
const int Motor_M1 = 10;     // 控制馬達1正反轉 digital pin 10 of Arduino
const int Motor_E2 = 6; // 控制馬達2轉速 digital pin 6 of Arduino (PWM)    
const int Motor_M2 = 11;    // 控制馬達2正反轉 digital pin 11 of Arduino

void setup() {
   //set up serial communications
   Serial.begin(57600);

  // 輸出入接腳初始設定
  pinMode(Motor_M1, OUTPUT);  //設定 Motor_M1為輸出腳位
  pinMode(Motor_M2, OUTPUT);  //設定 Motor_M2為輸出腳位
  pinMode(Motor_E1, OUTPUT);  //設定 Motor_E1為輸出腳位
  pinMode(Motor_E2, OUTPUT);  //設定 Motor_E2為輸出腳位

}

//////////// 主程式 ////////
void loop()
{
  forward(250);
  delay(1000);
  motorstop();  
  delay(1000);
  
  backward(250);
  delay(1000);
  motorstop();  
  delay(1000);
  
  right( 250);     //　　右轉
   delay(1000);
  motorstop();  
  delay(1000);

  left(250);      //　　左轉
  delay(1000);
  motorstop();
  delay(3000);
}

void motorstop()
{
  Serial.println("stop!");
  digitalWrite( Motor_E1, 0);
  digitalWrite( Motor_E2, 0);  
}

void forward(byte motorspeed)
{
  Serial.println("forward!");
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
}

void backward(byte motorspeed)
{
  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);
  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
}

void right(byte motorspeed)
{
  Serial.println("right!");  
  
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, motorspeed);
}

void left(byte motorspeed)
{
  Serial.println("left!");  
  
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, 0);

}


