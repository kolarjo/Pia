#include "Wire.h" //knihovna, která dovoluje komunikovat se zařízením 

 

const int MPU_ADDR = 0x68; //I2C adresa senzoru MPU-6050 z datasheetu
int16_t a_x, a_y, a_z; //zrychlení
int16_t gyro_x, gyro_y, gyro_z; //natočení
int16_t teplota; 
char tmp_str[7];//dočasná proměnná
char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

 

void setup() {
  Serial.begin(9600); //serial connection
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); //zahájení přenosu 
  Wire.write(0x6B);
  Wire.write(0); //snímač se probudí
  Wire.endTransmission(true);
 }

 

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // registr 0x3B pro modely MPU6000 a MPU6050 
  Wire.endTransmission(false); // parametr, který provede restart 
  Wire.requestFrom(MPU_ADDR, 7*2, true); // celkový počet 7*2 registrů
  
  a_x = Wire.read()<<8 | Wire.read(); // jsou uloženy dva registry stejné proměnné
  a_y = Wire.read()<<8 | Wire.read();
  a_z = Wire.read()<<8 | Wire.read();
  teplota  = Wire.read()<<8 | Wire.read();
  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read();
  gyro_z = Wire.read()<<8 | Wire.read();

 // vytiskneme data
  Serial.print((a_x)/16384.0); // musí se ještě vydělit 16384.0 a máme hodnoty v g (m^2/s)
  Serial.print(" ");Serial.print((a_y)/16384.0);
  Serial.print(" ");Serial.print((a_z)/16384.0);
 
  Serial.println();
  
  // delay 100ms
  delay(100);
}
