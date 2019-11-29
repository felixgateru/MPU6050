#include <Stepper.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <PID_v1.h>

MPU6050 mpu6050(Wire);



double Setpoint,Input,Output;
double Kp=1.0,Ki=1.0,Kd=1.0;
PID myPID(&Input,&Output,&Setpoint,Kp,Ki,Kd,DIRECT);

int stppr = 600;
float sttp;
Stepper myStepper ( stppr , 8, 10, 9 ,11);
float anglex;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Setpoint=0.0;
  Input=anglex;
  myPID.SetMode(AUTOMATIC);
  
}

void loop() {
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.println(mpu6050.getAngleX());
  anglex=mpu6050.getAngleX();
  Input=anglex;
  myPID.Compute();
  sttp=Output;
  sttp=sttp/0.17578125;
  myStepper.setSpeed(59);
  myStepper.step(sttp);
  

}
