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

float jacina = 255;
float korak = 25.5;
int prethodnoStanje = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(10, OUTPUT);
}

int ulaz;
int procenti = 100;

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  analogWrite(10, jacina);
  lcd.print("Jacina:");
  lcd.print(procenti);
  lcd.print("%");
  delay(100);

  ulaz = ocitajTaster();
  //int prethodnoStanje = 0;
  //int trenutnoStanje = 0;

  if(ulaz == 3 && jacina <= 229.5 && ulaz != prethodnoStanje)
  {
    jacina += korak;
    procenti += 10;
  }
  //trenutnoStanje = prethodnoStanje;
  else if(ulaz == 4 && jacina >= 25.5 && ulaz != prethodnoStanje)
  {
    jacina -= korak;
    procenti -= 10;
  }
  prethodnoStanje = ulaz;
}
