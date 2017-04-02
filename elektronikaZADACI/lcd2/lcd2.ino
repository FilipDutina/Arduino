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

int brojac = 0;
int ulaz;
int stanjePre;

void loop() {
  // put your main code here, to run repeatedly:
  ulaz = ocitajTaster();
  lcd.clear();
  lcd.print(brojac);
  delay(100);

  if(ulaz != stanjePre && ulaz == 3)
    brojac++;
  else if(ulaz != stanjePre && ulaz == 4)
    brojac--;

  stanjePre = ulaz;
}
