//Programa : Driver MPU6050
//Autor : Mateus Seixas
//Baseado no programa original de JohnChi

//Carrega a biblioteca Wire
#include<Wire.h>

#include <ros.h>
#include <std_msgs/Float32.h>
#include <Arduino.h>
#include <sensor_msgs/Imu.h>


ros::NodeHandle nh;
//std_msgs::Float32 Ax;
//ros::Publisher pub_Ax("Ax", &Ax);

//std_msgs::Float32 Ay;
//ros::Publisher pub_Ay("Ay", &Ay);
//
//std_msgs::Float32 Az;
//std_msgs::Float32 Gx;
//std_msgs::Float32 Gy;
//std_msgs::Float32 Gz;


//ros::Publisher pub_Az("Az", &Az);
//ros::Publisher pub_Gx("Gx", &Gx);
//ros::Publisher pub_Gy("Gy", &Gy);
//ros::Publisher pub_Gz("Gz", &Gz);

sensor_msgs::Imu imu;
//ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("data", 50);
ros::Publisher pub_imu("imu", &imu);


//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

const long PERIODO = 500;
unsigned long tempoAnterior = 0;

void setup()
{
//  Serial.begin(9600);
//  nh.getHardware()->setBaud(57600);
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
  nh.getHardware()->setBaud(57600);
  nh.initNode();
//  nh.advertise(pub_Ax);
//  nh.advertise(pub_Ay);
//  nh.advertise(pub_Az);
//  nh.advertise(pub_Gx);
//  nh.advertise(pub_Gy);
//  nh.advertise(pub_Gz);
  nh.advertise(pub_imu);
    
}
void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  //Envia os valores do acelerometro e do giroscópio para o serial sem conversão
//  Serial.print("AcX = ")ros; Serial.print(AcX);
//  Serial.print(" | AcY = "); Serial.print(AcY);
//  Serial.print(" | AcZ = "); Serial.print(AcZ);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
  
  //Envia os valores do acelerometro e do giroscópio para o serial com conversão
//  Serial.print("AcX = "); Serial.print(AcX/16384*9.80665);
//  Serial.print(" | AcY = "); Serial.print(AcY/16384*9.80665);
//  Serial.print(" | AcZ = "); Serial.print(AcZ/16384*9.80665);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
//  Serial.print(" | GyX = "); Serial.print(GyX/131*0.0174533);
//  Serial.print(" | GyY = "); Serial.print(GyY/131*0.0174533);
//  Serial.print(" | GyZ = "); Serial.println(GyZ/131*0.0174533);
 
  unsigned long tempoAtual = millis();
  
  if (tempoAtual - tempoAnterior >= PERIODO) {
    tempoAnterior = tempoAtual;
//    Ax.data = AcX/16384*9.80665;  
//    pub_Ax.publish(&Ax);
//    Ay.data = AcY/16384*9.80665; 
//    pub_Ay.publish(&Ay);
//    Az.data = AcZ/16384*9.80665; 
//    Gx.data = GyX/131*0.0174533;  
//    Gy.data = GyY/131*0.0174533; 
//    Gz.data = GyZ/131*0.0174533;
//
//    pub_Az.publish(&Az);
//    pub_Gx.publish(&Gx);
//    pub_Gy.publish(&Gy);
//    pub_Gz.publish(&Gz);

    imu.angular_velocity.x = GyX/131*0.0174533;
//    imu.angular_velocity.y = GyY/131*0.0174533;
//    imu.angular_velocity.z = GyZ/131*0.0174533;

//    imu.linear_acceleration.x = AcX/16384*9.80665;
//    imu.linear_acceleration.y = AcY/16384*9.80665;
//    imu.linear_acceleration.z = AcZ/16384*9.80665;

    pub_imu.publish(&imu);
    } 

  nh.spinOnce();
  //Aguarda 300 ms e reinicia o processo
  //delay(300);
}
