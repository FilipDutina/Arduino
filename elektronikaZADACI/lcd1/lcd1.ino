#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
byte ocitajTaster()
{
  int temp = analogRead(0);

  if(temp < 700 && temp > 600)
    return 1; //select
  else if(temp < 460 && temp > 360)
    return 2; //left
  else if(temp < 150 && temp > 50)
    return 3; //up
  else if(temp < 300 && temp > 200)
    return 4; //down
  else if(temp < 49)
    return 5; //right
  else
    return 0; //nista nije pritisnuto
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
}
int ulaz;

void loop() {
  // put your main code here, to run repeatedly:
  ulaz = ocitajTaster();

  if(ulaz == 0)
  {
    lcd.print(" ");
    delay(100);
    lcd.clear();
  }
  else if(ulaz == 1)
  {
    lcd.print("SELECT -> 1");
    delay(100);
    lcd.clear();
  }
  else if(ulaz == 2)
  {
    lcd.print("LEFT -> 2");
    delay(100);
    lcd.clear();
  }
  else if(ulaz == 3)
  {
    lcd.print("UP -> 3");
    delay(100);
    lcd.clear();
  }
  else if(ulaz == 4)
  {
    lcd.print("DOWN -> 4");
    delay(100);
    lcd.clear();
  }
  else
  {
    lcd.print("RIGHT -> 5");
    delay(100);
    lcd.clear();
  }
}
