#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte smajli[8] = {B00000, B00000, B01010, B00000, B10001, B01110, B00000, B00000};
int osaX = 0;
int osaY = 0;

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
  lcd.createChar(0, smajli);
}

int ulaz = 0;

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(osaX, osaY);
  lcd.write(byte(0));
  ulaz = ocitajTaster();
  delay(150);
  lcd.clear();

  if(ulaz == 5 && osaX < 15)
    osaX++;
  else if(ulaz == 2 && osaX > 0)  
    osaX--;
  else if(ulaz == 3 && osaY > 0)
    osaY--;
  else if(ulaz == 4 && osaY < 1)
    osaY++;
}
