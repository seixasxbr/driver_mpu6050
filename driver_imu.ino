//Programa : Driver MPU6050
//Autor : Mateus Seixas
//Baseado no programa original de JohnChi

//Carrega a biblioteca Wire
#include<Wire.h>

//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup()
{
  Serial.begin(9600);
  //Inicializa o LCD
//  lcd.begin(20, 4);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
    
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
//  Serial.print("AcX = "); Serial.print(AcX);
//  Serial.print(" | AcY = "); Serial.print(AcY);
//  Serial.print(" | AcZ = "); Serial.print(AcZ);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
  
  //Envia os valores do acelerometro e do giroscópio para o serial com conversão
  Serial.print("AcX = "); Serial.print(AcX/16384*9.80665);
  Serial.print(" | AcY = "); Serial.print(AcY/16384*9.80665);
  Serial.print(" | AcZ = "); Serial.print(AcZ/16384*9.80665);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
  Serial.print(" | GyX = "); Serial.print(GyX/131*0.0174533);
  Serial.print(" | GyY = "); Serial.print(GyY/131*0.0174533);
  Serial.print(" | GyZ = "); Serial.println(GyZ/131*0.0174533);

  
  //Aguarda 300 ms e reinicia o processo
  delay(300);
}
