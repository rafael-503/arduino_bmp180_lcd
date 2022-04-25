#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SFE_BMP180.h>

LiquidCrystal_I2C lcd(0x27,16,2);
SFE_BMP180 pressure;
 
void setup()
{
  lcd.begin();
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail");
    while (1);
  }
}
 
void loop()
{
  char status;
  double T, P;
  lcd.setBacklight(HIGH);
  
  status = pressure.startTemperature();
  if (status != 0) {
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0) {
      lcd.setCursor(0,0);
      lcd.print("T: ");
      lcd.print(T);
      lcd.print(" C");

      status = pressure.startPressure(3);

      if (status != 0) {
        delay(status);

        status = pressure.getPressure(P, T);
        if (status != 0) {
          lcd.setCursor(0,1);
          lcd.print("P: ");
          lcd.print(P);
          lcd.print(" hPa");
        }
      }
    }
    delay(1000);
  };
  delay(1000);
}